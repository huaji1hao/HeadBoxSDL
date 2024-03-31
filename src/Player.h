#pragma once
#include "Scyjz14ImageManager.h"
#include "Scyjz14TileManager.h"
class Player :
    public AgentBaseObject
{

public:
    Player(int xStart, int yStart, BaseEngine* pEngine, Scyjz14TileManager* pTileManager, std::string strURL = "resources/game/player/pistol.png",
        int frameWidth = 45, int frameHeight = 50, bool useTopLeftFor00 = true, bool bVisible = true)
        : AgentBaseObject(xStart, yStart, pEngine, strURL, frameWidth, frameHeight, useTopLeftFor00, bVisible), m_pTileManager(pTileManager)
    {
        m_direction = DOWN;
    }
    
    // when player is knocked away by enemy
    void knockedAway(int enemyX, int enemyY);

    void virtDoUpdate(int iCurrentTime) override;

    
protected:
    Scyjz14TileManager* m_pTileManager;
};

