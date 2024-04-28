#include "header.h"
#include "Scyjz14ImageManager.h"

Scyjz14ImageManager* Scyjz14ImageManager::g_pManager = nullptr;

Scyjz14ImageManager* Scyjz14ImageManager::get()
{
	if (g_pManager == nullptr)
		g_pManager = new Scyjz14ImageManager();
	return g_pManager;
}

Scyjz14Image Scyjz14ImageManager::loadImage(std::string imageURL, bool loadPermanently)
{
	return Scyjz14ImageManager::get()->getImagebyURL(imageURL, true/*Load*/, loadPermanently/*Keep it loaded?*/);
}

void Scyjz14ImageManager::destroyImageManager()
{
	if (g_pManager == nullptr)
		return;
	delete g_pManager;
	g_pManager = nullptr;
}

std::shared_ptr<Scyjz14RawImageData> Scyjz14ImageManager::getImagePtrbyURL(std::string imageURL, bool loadIfNotLoaded, bool loadPermanently)
{
	//std::cout << "\t\t+++ Find image: " << imageURL << std::endl;

	auto iter = images.find(imageURL);
	if (iter != images.end())
	{
		auto weak = iter->second; // Pull out pointer rather than key
		if (weak.expired())
		{
			// Remove the expired image from the list
			images.erase(iter);
			// And then carry on, to load it again
		}
		else
		{
			//std::cout << "\t\t+++ Find image: " << imageURL << " image found" << std::endl;

			auto shared = weak.lock(); // Convert to a shared pointer, which we are returning
			return shared; // Iterator points at the shared pointer
		}
	}

	// Otherwise either load it or return a null pointer
	if (loadIfNotLoaded)
	{
		std::cout << "\t\t+++ Load image: " << imageURL << std::endl;

		auto newSharedPtr = loadAsNew(imageURL); // Load image from file
		if (newSharedPtr != nullptr)
		{
			std::weak_ptr<Scyjz14RawImageData> weak = newSharedPtr; // Shared to weak pointer
			images.insert(std::pair<std::string, std::weak_ptr<Scyjz14RawImageData>>(imageURL, weak));
			if (loadPermanently) // Storing shared pointer keeps it alive while array exists - forever.
				permanentlyLoadedImages.insert(std::pair<std::string, std::shared_ptr<Scyjz14RawImageData>>(imageURL, newSharedPtr));
		}
		else
		{
			std::cout << "ImageManager::getImagePtrbyURL() : Failed to load image " << imageURL << std::endl;
		}
		return newSharedPtr; // Return the loading attempt result, whether successful or not
	}
	return nullptr; // failed
}


Scyjz14Image Scyjz14ImageManager::getImagebyURL(std::string imageURL, bool loadIfNotLoaded, bool loadPermanently)
{
	return Scyjz14Image(getImagePtrbyURL(imageURL, loadIfNotLoaded, loadPermanently));
}

bool Scyjz14ImageManager::setPermanentlyLoaded(std::string imageURL, bool makePermanent)
{
	if (makePermanent == false)
	{	// Take item out of permanentlyLoadedImages
		auto iter = permanentlyLoadedImages.find(imageURL);
		if (iter != permanentlyLoadedImages.end())
		{
			permanentlyLoadedImages.erase(iter);
			return true;
		}
		return false; // Can't remove because not in there
	}
	else
	{	// Find item in normal array and add to permanently loaded images
		// If already in permanentlyLoadedImages then nothing to do.
		auto iter = permanentlyLoadedImages.find(imageURL);
		if (iter != permanentlyLoadedImages.end())
			return true;
		// Otherwise look for the image...
		auto iter2 = images.find(imageURL);
		if (iter2 != images.end())
		{
			permanentlyLoadedImages.insert(std::pair<std::string, std::shared_ptr<Scyjz14RawImageData>>(iter2->first, iter2->second.lock()));
			return true;
		}
		return false;
	}
}

std::shared_ptr<Scyjz14RawImageData> Scyjz14ImageManager::loadAsNew(std::string imageURL)
{
	int cropLeft = 0, cropRight = 0, cropTop = 0, cropBottom = 0;
	Scyjz14RawImageData* pData = new Scyjz14RawImageData(imageURL);
	if (pData->loadImage(imageURL, 0, cropTop, cropBottom, cropLeft, cropRight))
	{
		return std::shared_ptr<Scyjz14RawImageData>(pData);
	}
	printf("Failed to load image %s\n", imageURL.c_str());
	delete pData; // Failed so no longer needed
	return nullptr;
}

Scyjz14ImageObject::Scyjz14ImageObject(int xStart, int yStart, 
	BaseEngine* pEngine, std::string strURL, 
	bool useTopLeftFor00, bool bVisible): 
	DisplayableObject(xStart, yStart, pEngine, 100, 100, useTopLeftFor00),
	image(Scyjz14ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/))
{
	m_iDrawWidth = image.getWidth();
	m_iDrawHeight = image.getHeight();
	// Offset within the drawing area to draw at - need to reset since width and height changed:
	m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
	m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
	setVisible(bVisible);
}

void Scyjz14ImageObject::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}