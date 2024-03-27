#pragma once
#include "TileManager.h"
class Scyjz14TileManager :
    public TileManager
{
public:
	Scyjz14TileManager(void) : TileManager(30, 30)
	{
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
};

