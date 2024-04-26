#include "header.h"
#include "Bullet.h"
#include "ObjectIndexes.h"
#include "Zombie.h"
#include "Scyjz14CollisionDetection.h"

void Bullet::onFire(int playerX, int playerY, SpriteObject::Direction direction) {
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

    checkZombieFired();
}

void Bullet::checkZombieFired() {
    for (auto& id : ObjectIndexes::getZombieIndexes()) {
        Zombie* zb = dynamic_cast<Zombie*>(getEngine()->getDisplayableObject(id));
        if (zb == nullptr || zb->isDied() || !zb->isVisible()) continue;
        if (Scyjz14CollisionDetection::checkPixelWithLine(zb->getImage(), zb->getCurrentFrameX() * zb->getDrawWidth(), zb->getDirection() * zb->getDrawHeight(), zb->getDrawWidth(), zb->getDrawHeight(), zb->getDrawingRegionLeft(), zb->getDrawingRegionTop(),
            m_iStartX, m_iStartY, m_iEndX, m_iEndY))
        {
            zb->lifeDecrease(damage);
            zb->checkIsKilled();
        }
    }
}

void Bullet::virtDraw() {
    int uColour = 0xa6a6a6;
    int bias = 3;
    if (getEngine()->getModifiedTime() <= disappearanceTime) {
        getEngine()->drawForegroundLine(m_iStartX, m_iStartY, m_iEndX, m_iEndY, uColour);

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
    }

}