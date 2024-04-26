#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "SpriteObject.h"

class Bullet :
    public DisplayableObject
{
public:
    Bullet(int xStart, int yStart, BaseEngine* pEngine, bool useTopLeftFor00 = true, bool bVisible = false)
    : DisplayableObject(xStart, yStart, pEngine, 50, 50, useTopLeftFor00)
    , m_iStartX(0), m_iStartY(0), m_iEndX(0), m_iEndY(0)
    {
    }

    void onFire(int playerX, int playerY, SpriteObject::Direction direction);

    void virtDraw();

    void checkZombieFired();

protected:
    int m_iStartX;
    int m_iStartY;
    int m_iEndX;
    int m_iEndY;
    int duration = 100;
    int disappearanceTime = 0;
    int damage = 5;
    int muzzleDistance = 20;
    int shootingDistance = 160;
    SpriteObject::Direction m_direction = SpriteObject::UP;
};

