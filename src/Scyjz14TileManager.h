#pragma once
#include "TileManager.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"

class Scyjz14TileManager :
    public TileManager
{
public:
	Scyjz14TileManager(void) : TileManager(40, 30)
	{
		tileImage = Scyjz14ImageManager::loadImage("resources/game/tiles.png", true);
		
	}

	~Scyjz14TileManager(void)
	{
	}

	// Draw a tile at a location on the screen determined by the tile position and the base X and Y co-ordinates
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	
	void setUpTileManager(BaseEngine* pEngine);

	bool isPassable(int tileType) const;

	bool isPassable(int iScreenX, int iScreenY) const;

	bool isPassableByObjectCentre(int iScreenX, int iScreenY, int offSet) const;


	enum Type { 
		NONE, WALL1, WALL2, WALL3, WALL4,
		WALL5, WALL6, WALL7, WALL8, BARREL
	};

protected:
	Scyjz14Image tileImage;
};

