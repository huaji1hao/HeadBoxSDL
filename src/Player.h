#pragma once
#include "ExampleObjects.h"
#include "Scyjz14TileManager.h"
class Player :
    public ImageObject
{

public:
    Player(BaseEngine* pEngine, Scyjz14TileManager* pTileManager, std::string strURL = "resources/oil.png", bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(pEngine, strURL, useTopLeftFor00, bVisible), m_pTileManager(pTileManager)
    {
    }
    /*Player(BaseEngine* pEngine, std::string strURL = "resources/oil.png", bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(pEngine, strURL, useTopLeftFor00, bVisible)
    {
    }*/

    Player(int xStart, int yStart, BaseEngine* pEngine, Scyjz14TileManager* pTileManager, std::string strURL = "resources/oil.png", bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible), m_pTileManager(pTileManager)
    {
    }
    
    // when player is knocked away by enemy
    void knockedAway(int enemyX, int enemyY);

    void virtDoUpdate(int iCurrentTime) override;

protected:
    Scyjz14TileManager* m_pTileManager;
};

