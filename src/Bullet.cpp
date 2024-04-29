#include "header.h"
#include "Bullet.h"
#include "ObjectIndexes.h"
#include "Zombie.h"
#include "Scyjz14CollisionDetection.h"

Bullet::Bullet(int xStart, int yStart, BaseEngine* pEngine, bool useTopLeftFor00, bool bVisible)
    : DisplayableObject(xStart, yStart, pEngine, 50, 50, useTopLeftFor00)
    , m_iStartX(0), m_iStartY(0), m_iEndX(0), m_iEndY(0)
{
    duration = 100;
    disappearanceTime = 0;
    damage = 5;
    muzzleDistance = 20;
    shootingDistance = 160;
    m_direction = SpriteObject::UP;
}

void Bullet::onFire(int playerX, int playerY, SpriteObject::Direction direction) {
    // Reset the disappearance time
    disappearanceTime = getEngine()->getModifiedTime() + duration;

    int startX = playerX, startY = playerY;
    int endX = playerX, endY = playerY;

    // Calculate the line endpoints based on direction
    switch (direction) {
    case SpriteObject::RIGHT:
        startX += muzzleDistance;
        endX += shootingDistance;
        break;
    case SpriteObject::UP:
        startY -= muzzleDistance;
        endY -= shootingDistance;
        break;
    case SpriteObject::LEFT:
        startX -= muzzleDistance;
        endX -= shootingDistance;
        break;
    case SpriteObject::DOWN:
        startY += muzzleDistance;
        endY += shootingDistance;
        break;
    }

    // prevent overflow
    m_iStartX = std::max(0, std::min(startX, getEngine()->getWindowWidth() - 1));
    m_iStartY = std::max(0, std::min(startY, getEngine()->getWindowHeight() - 1));

    m_iEndX = std::max(0, std::min(endX, getEngine()->getWindowWidth() - 1));
    m_iEndY = std::max(0, std::min(endY, getEngine()->getWindowHeight() - 1));

    m_direction = direction;
    
    // Check if the bullet hits the zombie
    checkZombieFired();
}

void Bullet::checkZombieFired() {
    for (auto& id : ObjectIndexes::getZombieIndexes()) {
        Zombie* zb = dynamic_cast<Zombie*>(getEngine()->getDisplayableObject(id));
        // Check if the zombie is dead or not visible
        if (zb == nullptr || zb->isDied() || !zb->isVisible()) continue;
        // If the bullet hits the zombie
        if (Scyjz14CollisionDetection::checkPixelWithStraightLine(zb->getImage(), zb->getCurrentFrameX() * zb->getDrawWidth(), zb->getDirection() * zb->getDrawHeight(), zb->getDrawWidth(), zb->getDrawHeight(), zb->getDrawingRegionLeft(), zb->getDrawingRegionTop(),
            m_iStartX, m_iStartY, m_iEndX, m_iEndY))
        {
            zb->lifeDecrease(zb->getIsBoss() ? 1 : damage);
            zb->checkIsKilled();
        }
    }
}

void Bullet::virtDraw() {
    int uColour = 0xa6a6a6;
    int bias = 3;

    // Draw the bullet if it is not disappeared
    if (getEngine()->getModifiedTime() <= disappearanceTime) {
        // Draw the bullet
        getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX, m_iEndY, uColour);

        // Draw the bullet with bias
        switch (m_direction) {
            case SpriteObject::LEFT:
            case SpriteObject::RIGHT:
                getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX, m_iEndY - bias, uColour);
                getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX, m_iEndY + bias, uColour);
                break;
            case SpriteObject::UP:          
            case SpriteObject::DOWN:
                getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX - bias, m_iEndY, uColour);
                getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX + bias, m_iEndY, uColour);
                break;
        }
    } else {
        setShouldDeleteOnRemoval(false);
    }

}