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
	static Scyjz14ImageManager* get();

	// Load an image into memory, and return a SimpleImage object which uses it
	// imageURL : the URL of the file to load
	// loadPermanently : keep the image in memory even when you stop using it in this image
	static Scyjz14Image loadImage(std::string imageURL, bool loadPermanently = false);

	/*
	Destroy the image manager object - note that this will destroy its maps which it contains
	Which will destroy the objects contained.
	*/
	static void destroyImageManager();

private:
	/* Singleton ImageManager object pointer. */
	static Scyjz14ImageManager* g_pManager;

public:

	// Constructor - just initialise the variables
	Scyjz14ImageManager()
	{
	}


	// Retrieve an image by its URL. If already loaded then it gets the existing one
	std::shared_ptr<Scyjz14RawImageData> getImagePtrbyURL(std::string imageURL, bool loadIfNotLoaded = false, bool loadPermanently = false);


	// Create a new ImageData object to represent the image and allow manipulation and rendering
	Scyjz14Image getImagebyURL(std::string imageURL, bool loadIfNotLoaded = false, bool loadPermanently = false);



	/*
	Specify whether an image should be permanently loaded or not.
	Keeps a shared pointer to the image data, which will keep it alive
	imageURL : the url of the image file
	makePermanent : true to keep it loaded, false to unload it as soon as nothing is actively using it
	*/
	bool setPermanentlyLoaded(std::string imageURL, bool makePermanent = true);

	// Load the image data into a NEW RawImageData object and return the shared pointer to it
	std::shared_ptr<Scyjz14RawImageData> loadAsNew(std::string imageURL);
};


class Scyjz14ImageObject : public DisplayableObject
{
public:
	// Constructors
	Scyjz14ImageObject(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true);

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw() override;

	Scyjz14Image getImage() { return image; }

protected:
	Scyjz14Image image;
};





