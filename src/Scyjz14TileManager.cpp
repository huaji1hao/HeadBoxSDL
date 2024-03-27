#include "header.h"
#include "Scyjz14TileManager.h"

void Scyjz14TileManager::setUpTileManager(BaseEngine* pEngine) {
	// Construct the map from a string
	const char* data[] = {
				"000000000000000000000000",
				"000000000000000000000000",
				"001100000000000000011000",
				"002200000000000000022000",
				"001100000000000000011000",
				"002200000000000000022000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
				"000000000000000000000000",
	};

	// Specify how many tiles wide and high
	setMapSize(24, 20);
	// Set up the tiles
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 24; x++)
			setMapValue(x, y, data[y][x] - '0');

	// Output the map to check
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 24; x++)
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
	// Draw the tiles based on their value
	switch (getMapValue(iMapX, iMapY))
	{
	case 0:
		// Do nothing
		break;
	case 1:
		// Draw a grey rectangle
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			pEngine->getColour(8));
		break;
	case 2:
		// Draw a black rectangle	
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			pEngine->getColour(0));
		// Draw a green oval centered in the tile
		pSurface->drawOval(
			iStartPositionScreenX + getMapValue(iMapX, iMapY) * 2 + 5,
			iStartPositionScreenY + getMapValue(iMapX, iMapY) * 2 + 5,
			iStartPositionScreenX + getTileWidth() - getMapValue(iMapX, iMapY) * 2 - 6,
			iStartPositionScreenY + getTileHeight() - getMapValue(iMapX, iMapY) * 2 - 6,
			pEngine->getColour(getMapValue(iMapX, iMapY)));
		break;
		
	}
}
