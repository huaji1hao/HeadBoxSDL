#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "ImagePixelMapping.h"
#include "ImagePixelMappingFlip.h"

static CroppedImagePixelMapping nullMapping;


// Standard constructor taking a pointer to the image which is being used
Scyjz14Image::Scyjz14Image(std::shared_ptr<Scyjz14RawImageData> theData)
	: theData(theData)
{
	m_pRescaleSurface = nullptr;
	m_iTransparencyColour = -1;
}

bool isColorSimilar(int color1, int color2, int tolerance) {
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	return abs(r1 - r2) <= tolerance && abs(g1 - g2) <= tolerance && abs(b1 - b2) <= tolerance;
}

//STOP!!!!
//You don't need to understand most of what is in this file.

void Scyjz14Image::renderImageWithAlpha(DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight) const {

	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight)) {
		return;
	}

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++) {
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++) {
			unsigned int iPixel = theData->getRawPixelColour(iXS, iYS);

			unsigned int alpha = iPixel >> 24;
			
			if (alpha > 0) { 
				if (alpha == 255) { 
					pTarget->setPixel(iXT, iYT, iPixel);
				}
				else {
					
					unsigned int backgroundPixel = pTarget->getPixel(iXT, iYT);
					unsigned int blendedPixel = blendPixels(backgroundPixel, iPixel, alpha);
					pTarget->setPixel(iXT, iYT, blendedPixel);
				}
			}
			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}
}

unsigned int Scyjz14Image::blendPixels(unsigned int background, unsigned int foreground, unsigned int alpha) const{
	unsigned int rb = ((background & 0xFF00FF) * (255 - alpha) + (foreground & 0xFF00FF) * alpha) >> 8;
	unsigned int g = ((background & 0x00FF00) * (255 - alpha) + (foreground & 0x00FF00) * alpha) >> 8;
	return (rb & 0xFF00FF) | (g & 0x00FF00) | 0xFF000000; // assume that the background is always opaque
}

void Scyjz14Image::renderImageWithAlphaAndOverlay(DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight, unsigned int backgroundcolour) const {
	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight)) {
		return;
	}

	backgroundcolour &= 0xFFFFFF;
	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++) {
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++) {
			unsigned int iPixel = theData->getRawPixelColour(iXS, iYS);

			unsigned int alpha = iPixel >> 24;

			unsigned int backgroundPixel = pTarget->getPixel(iXT, iYT) & 0xFFFFFF;
			
			if (backgroundPixel == backgroundcolour) {
				if (alpha > 0) {
					if (alpha == 255) {
						pTarget->setPixel(iXT, iYT, iPixel);
					}
					else {
						unsigned int blendedPixel = blendPixels(backgroundPixel, iPixel, alpha);
						pTarget->setPixel(iXT, iYT, blendedPixel);
					}
				}
			}

			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}

}


void Scyjz14Image::renderImageWithAlphaAndApplyingMapping(BaseEngine* pEngine, DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight,
	ImagePixelMapping* mapping) const {

	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight)) {
		return;
	}

	if (mapping == nullptr)
		mapping = &nullMapping;

	double dx, dy;
	int iPixel;
	auto my_mapping = dynamic_cast<ImagePixelMappingFlip*>(mapping);

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++) {
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++) {
			dx = iXSource + iXOffset;
			dy = iYSource + iYOffset;
			if (my_mapping->mapCoordinates(dx, dy, *this)) {
				iPixel = theData->getRawPixelColour(static_cast<int>(dx), static_cast<int>(dy));
				unsigned int alpha = iPixel >> 24;

				if (alpha > 0) {
					int actualX = iXTarget + iXOffset;
					int actualY = iYTarget + iYOffset;
					unsigned int finalColor = iPixel;

					if (alpha < 255) {
						unsigned int backgroundPixel = pTarget->getPixel(actualX, actualY);
						finalColor = blendPixels(backgroundPixel, iPixel, alpha);
					}

					// Assuming finalColor is initially defined as unsigned int
					int finalColorInt = static_cast<int>(finalColor);  // Convert unsigned int to int

					if (my_mapping->changePixelColour(actualX, actualY, finalColorInt, pTarget)) {
						pTarget->setPixel(actualX, actualY, static_cast<unsigned int>(finalColorInt));
					}
				}
			}
		}
	}
}