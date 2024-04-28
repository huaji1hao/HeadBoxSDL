#pragma once
#include "SpriteObject.h"
#include <vector>
#include "Player.h"

class Zombie :
    public AgentBaseObject
{
public:
    Zombie(int xStart, int yStart, 
        BaseEngine* pEngine, Scyjz14TileManager* pTileManager, 
        int revealTime = 0, int isBoss = false, 
        std::string strURL = "resources/game/zombie/zombies.png", int frameWidth = 45, int frameHeight = 50, 
        bool useTopLeftFor00 = true, bool bVisible = true);
    
    // Update the zombie's position
    void virtDoUpdate(int iCurrentTime) override;
    // Draw the zombie's body when it is killed
    void drawBody();
    // Draw the zombie
    void virtDraw() override;
    // Check if the zombie is killed
    void checkIsKilled();
    // Set the zombie as a boss
    void setBoss(bool isBoss);
    // Get whether the zombie is a boss
    bool getIsBoss() { return m_bIsBoss; }

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

    // Update the zombie's animation frame
    void updateAnimationFrame(int iCurrentTime) override;
    // Update the zombie's direction
    void updateDirection(int dx, int dy);
    // Update the zombie's direction towards the player
    void updateDirectionTowardsPlayer(Player* player);
    // Attack the player
    void attackPlayer();
    // Fixed zombie positions to try to avoid overlap between zombies
    void fixPosition() override;
        
protected:
    bool m_bIsBoss = false;
};

