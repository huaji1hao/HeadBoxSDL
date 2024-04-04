#pragma once
#include "SpriteObject.h"
#include <vector>
#include "Player.h"

class Zombie :
    public AgentBaseObject
{
public:
    Zombie(int xStart, int yStart, BaseEngine* pEngine, Scyjz14TileManager* pTileManager, std::string strURL = "resources/game/zombie/zombie_8.png",
        int frameWidth = 45, int frameHeight = 50, bool useTopLeftFor00 = true, bool bVisible = true)
        : AgentBaseObject(xStart, yStart, pEngine, strURL, frameWidth, frameHeight, useTopLeftFor00, bVisible)
    {
        m_direction = UP;
        m_pTileManager = pTileManager;
        setSpeed(2);
        setFrameRate(30);
    }
    

    virtual void virtDoUpdate(int iCurrentTime) override;

    void drawBody();

protected:

    struct DirectionVector {
        int dx, dy;
        Direction dir;
    };

    const std::vector<DirectionVector> directionVectors = {
        {0, -1, UP},
        {0, 1, DOWN},
        {-1, 0, LEFT},
        {1, 0, RIGHT},
        {-1, -1, UPLEFT},
        {1, -1, UPRIGHT},
        {-1, 1, DOWNLEFT},
        {1, 1, DOWNRIGHT},
    };

    virtual void updateAnimationFrame(int iCurrentTime) override;

    void updateDirection(int dx, int dy);

    void updateDirectionTowardsPlayer(Player* player);

    // the function to attack all the player
    virtual void attackPlayer();

    void fixPosition() override;

};

