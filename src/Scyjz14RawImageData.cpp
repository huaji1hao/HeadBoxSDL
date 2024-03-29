#include "header.h"
#include "Scyjz14RawImageData.h"

int Scyjz14RawImageData::getRawPixelColour(int iX, int iY) const {
	if (m_aiPixels == nullptr) {
		return 0;
	}
	return 0xffffffff & (m_aiPixels[(iY % m_iHeight) * m_iWidth + (iX % m_iWidth)]);
}

bool Scyjz14RawImageData::loadImage(std::string strFileName, int num90degRotations, int cropTop, int cropBottom, int cropLeft, int cropRight, bool cacheSurface)
{
	const char* szFileName = strFileName.c_str();

	SDL_Surface* loadedSurface = IMG_Load(szFileName);
	if (loadedSurface != nullptr)
	{
		// Make a 32 bit version
		SDL_Surface* tempSurface = SDL_CreateRGBSurface(
			SDL_SWSURFACE, loadedSurface->w, loadedSurface->h, 32,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		//SDL_Rect dest = { cropLeft, cropTop, m_imagesurface->w - cropRight , m_imagesurface->h - cropBottom };
		SDL_BlitSurface(loadedSurface, NULL, tempSurface, NULL);
		SDL_FreeSurface(loadedSurface);

		if ((num90degRotations % 2) == 1)
		{
			m_iWidth = tempSurface->h - cropTop - cropBottom;
			m_iHeight = tempSurface->w - cropLeft - cropRight;
		}
		else
		{
			m_iWidth = tempSurface->w - cropLeft - cropRight;
			m_iHeight = tempSurface->h - cropTop - cropBottom;
		}

		// Free any current surface
		freeSurface();

		// Create the new surface for use
		m_pImagesurface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_iWidth, m_iHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		if (m_pImagesurface == nullptr)
		{
			printf("Error creating surface in RawImage::loadImage() !");
		}
		else
		{
			m_aiPixels = (unsigned int*)m_pImagesurface->pixels;

			int iIntsPerScreenRow = tempSurface->pitch / sizeof(unsigned int);

			for (int iY = 0; iY < m_iHeight; iY++)
			{
				for (int iX = 0; iX < m_iWidth; iX++)
				{
					// Calculate which pixel to pull from the image
					m_aiPixels[iY * m_iWidth + iX] = (((unsigned int*)tempSurface->pixels)[getXForRotationAndCrop(tempSurface->w, iX, iY, num90degRotations, cropLeft, cropTop) + getYForRotationAndCrop(tempSurface->h, iX, iY, num90degRotations, cropLeft, cropTop) * iIntsPerScreenRow]);

					//std::cout << (m_aiPixels[iY * m_iWidth + iX] >> 24) << " "; // output alpha, just to check it - seems to be ff for everything
				}
			}

			return true;
		}
	}
	return false;
}