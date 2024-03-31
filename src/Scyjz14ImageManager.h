#pragma once

#include <map>
#include <string>
#include <memory>

#include "SimpleImage.h"
#include "Scyjz14RawImageData.h"
#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"

/*
The ImageManager manages loaded images. The main aim is that it avoid re-loading images which are already loaded, sharing them between objects.
Images are loaded as RawImageData objects.
SimpleImage and ImageRenderer are front ends to the image data, specifying which pixels to draw from that image.
Uses smart pointers and maps to maintain the list, so may be worth looking at for that reason?
*/
class Scyjz14ImageManager
{
	// Store the data for the images, by URL loaded from
	std::map<std::string, std::weak_ptr<Scyjz14RawImageData> > images;
	// These images are kept permanently loaded
	std::map<std::string, std::shared_ptr<Scyjz14RawImageData> > permanentlyLoadedImages;

public:
	// Singleton implementation, if desired, use static get() to get the singleton object.
	static Scyjz14ImageManager* get()
	{
		if (g_pManager == nullptr)
			g_pManager = new Scyjz14ImageManager();
		return g_pManager;
	}

	// Load an image into memory, and return a SimpleImage object which uses it
	// imageURL : the URL of the file to load
	// loadPermanently : keep the image in memory even when you stop using it in this image
	static Scyjz14Image loadImage(std::string imageURL, bool loadPermanently = false)
	{
		return Scyjz14ImageManager::get()->getImagebyURL(imageURL, true/*Load*/, loadPermanently/*Keep it loaded?*/);
	}

	/*
	Destroy the image manager object - note that this will destroy its maps which it contains
	Which will destroy the objects contained.
	*/
	static void destroyImageManager()
	{
		if (g_pManager == nullptr)
			return;
		delete g_pManager;
		g_pManager = nullptr;
	}

private:
	/* Singleton ImageManager object pointer. */
	static Scyjz14ImageManager* g_pManager;

public:

	// Constructor - just initialise the variables
	Scyjz14ImageManager()
	{
	}


	// Retrieve an image by its URL. If already loaded then it gets the existing one
	std::shared_ptr<Scyjz14RawImageData> getImagePtrbyURL(std::string imageURL, bool loadIfNotLoaded = false, bool loadPermanently = false)
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


	// Create a new ImageData object to represent the image and allow manipulation and rendering
	Scyjz14Image getImagebyURL(std::string imageURL, bool loadIfNotLoaded = false, bool loadPermanently = false)
	{
		return Scyjz14Image(getImagePtrbyURL(imageURL, loadIfNotLoaded, loadPermanently));
	}



	/*
	Specify whether an image should be permanently loaded or not.
	Keeps a shared pointer to the image data, which will keep it alive
	imageURL : the url of the image file
	makePermanent : true to keep it loaded, false to unload it as soon as nothing is actively using it
	*/
	bool setPermanentlyLoaded(std::string imageURL, bool makePermanent = true)
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

	// Load the image data into a NEW RawImageData object and return the shared pointer to it
	std::shared_ptr<Scyjz14RawImageData> loadAsNew(std::string imageURL)
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
};


class Scyjz14ImageObject : public DisplayableObject
{
public:
	// Constructors
	Scyjz14ImageObject(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(xStart, yStart, pEngine, 100, 100, useTopLeftFor00),
		image(Scyjz14ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/))
	{
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(bVisible);
	}

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw() override
	{
		if (isVisible())
		{
			image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}


protected:
	Scyjz14Image image;
};


class SpriteObject : public Scyjz14ImageObject {
public:
	// Constructor to initialize the sprite object with a sprite sheet URL and frame dimensions
	
	SpriteObject(int xStart, int yStart, BaseEngine* pEngine, const std::string& strURL,
		int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true)
		: Scyjz14ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible){
		
		// Assuming that the sprite sheet's individual frame size is the same as the object's drawing size
		m_iDrawWidth = frameWidth;
		m_iDrawHeight = frameHeight;
	}
	

	// Override virtDraw to render the current frame of the sprite sheet
	virtual void virtDraw() override {
		if (isVisible()) {
			// Calculate the source position based on the current frame indices
			int iXSource = m_iCurrentFrameX * m_iDrawWidth;
			int iYSource = m_iCurrentFrameY * m_iDrawHeight;

			// Draw the current frame with transparency
			image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}
	}

	// Function to set the current frame based on the sprite sheet
	void setCurrentFrame(int frameX, int frameY) {
		m_iCurrentFrameX = frameX;
		m_iCurrentFrameY = frameY;
	}

	void setFrameRate(int frameRate) {
		// A second can have 1000ms / frameRate frams
		m_iTimeBetweenFrames = 1000 / frameRate;
	}

protected:
	// Function to update the animation frame based on the elapsed time
	virtual void updateAnimationFrame(int iCurrentTime) {
		// Calculate the time elapsed since the last frame update
		int iElapsedTime = iCurrentTime - m_iLastUpdateTime;

		// Check if it is time to update the frame
		if (iElapsedTime >= m_iTimeBetweenFrames) {
			// Update the frame index
			m_iCurrentFrameX = (m_iCurrentFrameX + 1) % getFrameCount();
			// Reset the last update time
			m_iLastUpdateTime = iCurrentTime;
		}
	}

	// Helper function to get the frame count based on the sprite sheet and direction
	// Assuming that the frame count is the same for all directions
	// and that all frames are evenly spaced in the sprite sheet
	virtual int getFrameCount() = 0;
	
	int m_iTimeBetweenFrames = 100; // Time between frames in milliseconds
	int m_iLastUpdateTime = 0; // Last time the frame was updated

	int m_iCurrentFrameX = 0;  // X index of the current frame
	int m_iCurrentFrameY = 0;;  // Y index of the current frame
};


class AgentBaseObject : public SpriteObject {
public:
	
	// Define an enumeration for the directions the sprite object can face
	enum Direction { UP, DOWN, LEFT, RIGHT };

	AgentBaseObject(int xStart, int yStart, BaseEngine* pEngine, const std::string& strURL,
		int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true)
		: SpriteObject(xStart, yStart, pEngine, strURL, frameWidth, frameHeight, useTopLeftFor00, bVisible) {
		m_direction = UP; // Default direction
	}

	// Function to draw the Agent
	virtual void virtDraw() override {
		if (isVisible()) {
			// Calculate the source position based on the current direction and frame index
			int iXSource = m_iCurrentFrameX * m_iDrawWidth;
			// Assuming each direction is in a different row
			int iYSource = m_direction * m_iDrawHeight;
			// Draw the current frame with transparency
			image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}
	}

	void setSpeed(int speed) { moving_speed = speed; }


protected:
	Direction m_direction; // Current direction the object faces
	int moving_speed = 1;

	virtual int getFrameCount() override{
		// Manually count that it is 8 for player
		return 8;
	}
};