#pragma once
#include "TileManager.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include <fstream>

class Scyjz14TileManager :
    public TileManager
{
public:
	Scyjz14TileManager(void);

	~Scyjz14TileManager(void) {}

	// Draw a tile at a location on the screen determined by the tile position and the base X and Y co-ordinates
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	
	// Set up the tile manager to use a specified tile map file
	void setUpTileManager(BaseEngine* pEngine, const char* filename);

	// Check if a tile is passable by checking the tile type
	bool isPassable(int tileType) const;

	// Check if a tile is passable by checking the screen position
	bool isPassable(int iScreenX, int iScreenY) const;

	// Check if a tile is passable by checking the screen position with an offset
	bool isPassableByObjectCentre(int iScreenX, int iScreenY, int offSet) const;

	// Load the map from a file
	bool loadMapFromFile(const char* filename);

	// Draw all the tiles
	void drawAllTiles(BaseEngine* pEngine, DrawingSurface* pSurface, int offsetX, int offsetY) const;

	// Get a random passable point on the map
	std::pair<int, int> getRandomPassablePoint();

	// The type of the tile
	enum Type { 
		NONE, WALL1, WALL2, WALL3, WALL4,
		WALL5, WALL6, WALL7, MECHANISM, BARREL, MECHANISM_PRESSED,
	};

protected:
	Scyjz14Image tileImage;
};

