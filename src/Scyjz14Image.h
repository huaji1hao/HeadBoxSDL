#pragma once
#include "SimpleImage.h"
class Scyjz14Image :
    public SimpleImage
{
public:
	Scyjz14Image::Scyjz14Image(const SimpleImage& simpleImage) : SimpleImage(simpleImage) {
	}

	// Render the image with transparency and mapping
	void renderImageApplyingMappingAndTransparency(BaseEngine* pEngine, DrawingSurface* pTarget,
		int iXDrawLocation, int iYDrawLocation, int iWidth, int iHeight,
		ImagePixelMapping* mapping) const;
};
