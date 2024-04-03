#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "ImagePixelMapping.h"

static CroppedImagePixelMapping nullMapping;


// Standard constructor taking a pointer to the image which is being used
Scyjz14Image::Scyjz14Image(std::shared_ptr<Scyjz14RawImageData> theData)
	: theData(theData)
{
	m_pRescaleSurface = nullptr;
	m_iTransparencyColour = -1;
}


void Scyjz14Image::renderImageApplyingMappingAndTransparency(BaseEngine* pEngine, DrawingSurface* pTarget,
	int iXDrawLocation, int iYDrawLocation, int iWidth, int iHeight,
	ImagePixelMapping* mapping) const
{
	if (mapping == nullptr)
		mapping = &nullMapping;

	int xStart = iXDrawLocation;
	int yStart = iYDrawLocation;
	int xMinOffset = 0;
	int xMaxOffset = iWidth;
	int yMinOffset = 0;
	int yMaxOffset = iHeight;

	int iLHS = pEngine->convertClickedToVirtualPixelXPosition(0);
	int iTop = pEngine->convertClickedToVirtualPixelYPosition(0);
	int iRHS = pEngine->convertClickedToVirtualPixelXPosition(pEngine->getWindowWidth());
	int iBottom = pEngine->convertClickedToVirtualPixelYPosition(pEngine->getWindowHeight());

	if (!pEngine->getRedrawAllScreen())
	{
		if ((xStart + iWidth < pEngine->getRedrawRectVirtualLeft())
			|| (xStart > pEngine->getRedrawRectVirtualRight())
			|| (yStart + iHeight < pEngine->getRedrawRectVirtualTop())
			|| (yStart > pEngine->getRedrawRectVirtualBottom()))
		{
			//std::cout << "Ignore piece outside redraw region" << std::endl;
			return;
		}
	}
	else
	{
		if ((xStart > iRHS)
			|| (xStart + iWidth < iLHS)
			|| (yStart > iBottom)
			|| (yStart + iHeight < iTop))
		{
			//std::cout << "Ignore piece off screen" << std::endl;
			return;
		}
	}

	if (xStart + xMinOffset < iLHS)
		xMinOffset = iLHS - xStart;
	//	if (yStart + yMinOffset + iWidth < iTop)
	//        xMinOffset = iLHS - xStart;
	if (yStart + yMinOffset < iTop)
		yMinOffset = iTop - yStart;

	if (xStart + xMaxOffset > iRHS)
		xMaxOffset = iRHS - xStart;
	if (yStart + yMaxOffset > iBottom)
		yMaxOffset = iBottom - yStart;

	// Note: this method can also handle partial redraw of screen, by reducing the size of the draw area:
	if (!pEngine->getRedrawAllScreen())
	{
		int iRedrawPos = pEngine->getRedrawRectVirtualLeft();
		if (iRedrawPos > xStart + xMinOffset)
			xMinOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualTop();
		if (iRedrawPos > yStart + yMinOffset)
			yMinOffset = iRedrawPos - yStart;
		iRedrawPos = pEngine->getRedrawRectVirtualRight();
		if (iRedrawPos < xStart + xMaxOffset)
			xMaxOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualBottom();
		if (iRedrawPos < yStart + yMaxOffset)
			yMaxOffset = iRedrawPos - yStart;
	}

	// Check for not visible
	if (xMaxOffset <= xMinOffset)
	{
		//std::cout << "Image not in x visible area" << std::endl;
		return;
	}
	if (yMaxOffset <= yMinOffset)
		return;

	double dx, dy;
	int iPixel;
	//std::cout << "Draw from " << xMinOffset << " to " << xMaxOffset << std::endl;
	for (int iYOffset = yMinOffset; iYOffset < yMaxOffset; ++iYOffset)
	{
		for (int iXOffset = xMinOffset; iXOffset < xMaxOffset; ++iXOffset)
		{
			dx = iXOffset;
			dy = iYOffset;
			if (mapping->mapCoordinates(dx, dy, *this))
			{ // It mapcoordinates returns false, do not draw the pixel
				int iColour = 0xffffff & theData->getRawPixelColour((int)(dx + 0.5), (int)(dy + 0.5));
				if (mapping->changePixelColour(iXDrawLocation + iXOffset, iYDrawLocation + iYOffset, iColour, pTarget))
				{ 
					if ((m_iTransparencyColour == -1) || iColour != m_iTransparencyColour)
						// If changePixelColour returns false it means we should not draw the pixel
						pTarget->setPixel(iXDrawLocation + iXOffset, iYDrawLocation + iYOffset, iColour);
				}
			}
		}
	}
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
	return (rb & 0xFF00FF) | (g & 0x00FF00) | 0xFF000000; // 假定背景总是完全不透明
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