#pragma once
#include "SimpleImage.h"
#include "Scyjz14RawImageData.h"

class Scyjz14Image :
    public SimpleImage
{
public:
	Scyjz14Image::Scyjz14Image(const SimpleImage& simpleImage) : SimpleImage(simpleImage) {
	}

	Scyjz14Image(std::shared_ptr<Scyjz14RawImageData> theData);

	int getWidth() const { return theData->getWidth(); }

	// Ask for the height of the image
	int getHeight() const { return theData->getHeight(); }

	// Get the colour of a specified pixel, by x and y position
	int getPixelColour(int x, int y) const { return theData->getRawPixelColour(x, y); }


	// Render the image with transparency and mapping
	void renderImageApplyingMappingAndTransparency(BaseEngine* pEngine, DrawingSurface* pTarget,
		int iXDrawLocation, int iYDrawLocation, int iWidth, int iHeight,
		ImagePixelMapping* mapping) const;


	void renderImageWithAlpha(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight) const;

	unsigned int blendPixels(unsigned int background, unsigned int foreground, unsigned int alpha) const;

private:
	std::shared_ptr<Scyjz14RawImageData> theData;

};
