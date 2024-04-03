#include "header.h"
#include "Scyjz14TileManager.h"

void Scyjz14TileManager::setUpTileManager(BaseEngine* pEngine) {
	// Construct the map from a string
	const char* data[] = {
				"000000000000000000000000",
				"000000000000000000000000",
				"001100000000000000011000",
				"002200000000000000022000",
				"001100989009000900091000",
				"002200000000000000029000",
				"000000000000000000000000",
				"000000000000000000000000",
				"003456000000000000000000",
				"000000000000000000000000",
				"000000000789000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
	};

	// Specify how many tiles wide and high
	setMapSize(24, 14);
	// Set up the tiles
	for (int y = 0; y < getMapHeight(); y++)
		for (int x = 0; x < getMapWidth(); x++)
			setMapValue(x, y, data[y][x] - '0');

	// Output the map to check
	for (int y = 0; y < getMapHeight(); y++) {
		for (int x = 0; x < getMapWidth(); x++)
			std::cout << getMapValue(x, y);
		std::cout << std::endl;
	}

	// Specify the screen x,y of top left corner
	drawAllTiles(pEngine, pEngine->getBackgroundSurface());
}


void Scyjz14TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iXSource = -1;
	// Draw the tiles based on their value
	switch (getMapValue(iMapX, iMapY))
	{
	
	case NONE:
		// Draw None
		break;
	case WALL1:
		iXSource = 1;
		break;
	case WALL2:
		iXSource = 2;
		break;
	case WALL3:
		iXSource = 3;
		break;
	case WALL4:
		iXSource = 4;
		break;
	case WALL5:
		iXSource = 5;
		break;
	case WALL6:
		iXSource = 6;
		break;
	case WALL7:
		iXSource = 7;
		break;
	case WALL8:
		iXSource = 8;
		break;
	case BARREL:
		iXSource = 0;
		break;
	}

	iXSource *= m_iTileWidth;

	if (iXSource >= 0) {

		tileImage.renderImageWithAlpha(pEngine->getBackgroundSurface(),
			iXSource, 0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			m_iTileWidth, m_iTileHeight);
	}
	else {
		// background
		pSurface->drawRectangle(
			iStartPositionScreenX,	// Left
			iStartPositionScreenY,	// Top
			iStartPositionScreenX + getTileWidth() - 1,		// Right
			iStartPositionScreenY + getTileHeight() - 1,	// Bottom
			0xEBDCC7);	// Pixel colour

	}
	
}

bool Scyjz14TileManager::isPassable(int tileType) const {
	switch (tileType) {
	case NONE:
		return true; // NONE can pass
	case WALL1:
	case WALL2:
	case WALL3:
	case WALL4:
	case WALL5:
	case WALL6:
	case WALL7:
	case WALL8:
	case BARREL:
		return false; // barrier
	default:
		return true;
	}
}

bool Scyjz14TileManager::isPassable(int iScreenX, int iScreenY) const {
	int tileX = getMapXForScreenX(iScreenX);
	int tileY = getMapYForScreenY(iScreenY);
	int mapValue = getMapValue(tileX, tileY);
	return isPassable(mapValue);
}

bool Scyjz14TileManager::isPassableByObjectCentre(int iScreenX, int iScreenY, int offSet) const {
	bool isLeftCentrePassible = isPassable(iScreenX - offSet, iScreenY);
	bool isRightCentrePassible = isPassable(iScreenX + offSet, iScreenY);

	return isLeftCentrePassible && isRightCentrePassible;
}



