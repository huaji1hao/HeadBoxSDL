#pragma once
#include "SimpleImage.h"
#include "Scyjz14RawImageData.h"

class Scyjz14Image :
    public SimpleImage
{
public:
	Scyjz14Image(){}

	Scyjz14Image::Scyjz14Image(const SimpleImage& simpleImage) : SimpleImage(simpleImage) {
	}

	Scyjz14Image(std::shared_ptr<Scyjz14RawImageData> theData);

	bool exists() const { return theData != nullptr; }

	int getWidth() const { return theData->getWidth(); }

	// Ask for the height of the image
	int getHeight() const { return theData->getHeight(); }

	// Get the colour of a specified pixel, by x and y position
	int getPixelColour(int x, int y) const { return theData->getRawPixelColour(x, y); }

	// Draw this image with transparency
	void renderImageWithAlpha(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight) const;

	// Only draw the part which background is a specfic color
	void renderImageWithAlphaAndOverlay(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight, unsigned int backgroundColour) const;

	// Only draw the part which background is these two specfic colors
	void renderImageWithAlphaAndTwoOverlay(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight, unsigned int backgroundColour1, unsigned int backgroundColour2) const;

	// Draw this image with transparency and apply a mapping to the pixels
	void renderImageWithAlphaAndApplyingMapping(BaseEngine* pEngine, DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight,
		ImagePixelMapping* mapping) const;

	// Algorithm to blend two pixels together - this is a simple alpha blend
	unsigned int blendPixels(unsigned int background, unsigned int foreground, unsigned int alpha) const;

private:
	std::shared_ptr<Scyjz14RawImageData> theData;

};
