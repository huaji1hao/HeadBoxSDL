#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "SpriteObject.h"

class Bullet :
    public DisplayableObject
{
public:
    Bullet(int xStart, int yStart, BaseEngine* pEngine, bool useTopLeftFor00 = true, bool bVisible = false);
    
    // make the bullet appear for a short time
    void onFire(int playerX, int playerY, SpriteObject::Direction direction);

    // draw the bullet
    void virtDraw();

    // check if the bullet hits the zombie
    void checkZombieFired();

protected:
    int m_iStartX; // start position x
    int m_iStartY; // start position y
    int m_iEndX; // end position x
    int m_iEndY; // end position y
    int duration; // how long the bullet will appear
    int disappearanceTime; // when the bullet will disappear
    int damage; // how much damage the bullet will cause
    int muzzleDistance; // the distance from the player to the muzzle
    int shootingDistance; // the distance the bullet will travel
    SpriteObject::Direction m_direction; // the direction the bullet is fired
};

