#pragma once

#include "header.h"
#include "RawImageData.h"

class Scyjz14RawImageData :
	public RawImageData
{
public:
	Scyjz14RawImageData(std::string filename) : RawImageData(filename) {}

	// Get the colour of a specified pixel, by x and y position within the image
	int getRawPixelColour(int iX, int iY) const;

	// Load the image with the specified filename
	bool loadImage(std::string strFileName, int num90degRotations = 0, int cropTop = 0, int cropBottom = 0, int cropLeft = 0, int cropRight = 0, bool cacheSurface = false);

};



