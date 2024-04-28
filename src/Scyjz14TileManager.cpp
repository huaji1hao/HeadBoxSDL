#include "header.h"
#include "Scyjz14TileManager.h"

Scyjz14TileManager::Scyjz14TileManager(void) : TileManager(40, 30)
{
	tileImage = Scyjz14ImageManager::loadImage("resources/game/tiles.png", true);
	srand(time(NULL));
}

bool Scyjz14TileManager::loadMapFromFile(const char* filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		// First two integers are the width and height of the map
		int width, height;
		file >> width >> height;
		setMapSize(width, height);

		// Read the map from the file
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				char value;
				file >> value;
				setMapValue(x, y, value - '0');
			}
		}

		file.close();
		return true;
	}
	else {
		printf("Something wrong when reading files\n");
		return false;
	}
}

std::pair<int, int> Scyjz14TileManager::getRandomPassablePoint() {
	int attempts = 0;
	const int MAX_ATTEMPTS = 100;  // set a max value to prevent infinite loop

	while (attempts < MAX_ATTEMPTS) {
		int x = rand() % getMapWidth();
		int y = rand() % getMapHeight();

		if (getMapValue(x, y) == 0) {  // check is the point passible
			// convert the screen position to map position
			int screenX = x * getTileWidth();
			int screenY = y * getTileHeight();
			return std::make_pair(screenX, screenY);
		}
		attempts++;
	}

	return std::make_pair(-1, -1);  // special value when failed
}

void Scyjz14TileManager::setUpTileManager(BaseEngine* pEngine, const char* filename) {
	// Load the map from the file first
	if (!loadMapFromFile(filename)) {
		printf("Load Map Error!\n");
		return;
	}
	
	// Output the map to check
	for (int y = 0; y < getMapHeight(); y++) {
		for (int x = 0; x < getMapWidth(); x++)
			std::cout << getMapValue(x, y);
		std::cout << std::endl;
	}

	// Specify the screen x,y of top left corner
	TileManager::drawAllTiles(pEngine, pEngine->getBackgroundSurface());
}


void Scyjz14TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iXSource = -1;
	// Draw the tiles based on their value
	switch (getMapValue(iMapX, iMapY)) {
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
	case MECHANISM:
		iXSource = 9;
		break;
	case BARREL:
		iXSource = 0;
		break;
	case MECHANISM_PRESSED:
		iXSource = 10;
		break;
	}

	iXSource *= m_iTileWidth;

	// Draw the tile if it is not NONE
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

void Scyjz14TileManager::drawAllTiles(BaseEngine* pEngine, DrawingSurface* pSurface, int offsetX, int offsetY) const
{
	pSurface->mySDLLockSurface();
	for (int iTX = 0; iTX < m_iMapWidth; iTX++)
	{
		for (int iTY = 0; iTY < m_iMapHeight; iTY++)
		{
			// Draw the tile with the specified offset
			virtDrawTileAt(pEngine, pSurface,
				iTX, iTY,
				m_iBaseScreenX + getTileWidth() * iTX + offsetX,
				m_iBaseScreenY + getTileHeight() * iTY + offsetY);
		}
	}
	pSurface->mySDLUnlockSurface();
}

bool Scyjz14TileManager::isPassable(int tileType) const {
	switch (tileType) {
	case NONE:
	case MECHANISM:
		return true; // NONE  and MECHANISM are passable
	case WALL1:
	case WALL2:
	case WALL3:
	case WALL4:
	case WALL5:
	case WALL6:
	case WALL7:
	case BARREL:
		return false; // barrier
	default:
		return true;
	}
}

bool Scyjz14TileManager::isPassable(int iScreenX, int iScreenY) const {
	// Convert the screen position to map position
	int tileX = getMapXForScreenX(iScreenX);
	int tileY = getMapYForScreenY(iScreenY);
	int mapValue = getMapValue(tileX, tileY);
	// Check if the tile is passable
	return isPassable(mapValue);
}

bool Scyjz14TileManager::isPassableByObjectCentre(int iScreenX, int iScreenY, int offSet) const {
	// Check if the centre of the object with the offset is passable
	bool isLeftCentrePassible = isPassable(iScreenX - offSet, iScreenY);
	bool isRightCentrePassible = isPassable(iScreenX + offSet, iScreenY);
	
	// Return true if both centres are passible
	return isLeftCentrePassible && isRightCentrePassible;
}



