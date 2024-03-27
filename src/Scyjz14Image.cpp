#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "ImagePixelMapping.h"

static CroppedImagePixelMapping nullMapping;

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