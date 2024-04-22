#include "Weapon.h"
#include "Zombie.h"
#include "Scyjz14CollisionDetection.h"
#include "Scyjz14Engine.h"

int Weapon::getWeaponX() {
    if (m_direction == LEFT) return m_pPlayer->getDrawingRegionLeft() - distance;
    else if (m_direction == RIGHT) return m_pPlayer->getDrawingRegionLeft() + distance;
    else return m_pPlayer->getDrawingRegionLeft();
}

int Weapon::getWeaponY() {
    if (m_direction == UP) return m_pPlayer->getDrawingRegionTop() - distance;
    else if (m_direction == DOWN) return m_pPlayer->getDrawingRegionTop() + distance;
    else return m_pPlayer->getDrawingRegionTop();
}

void Weapon::virtDoUpdate(int iCurrentTime) {
    if (!isVisible() || getEngine()->isPaused())
        return;

    for (const auto& pair : movements) {
        SDL_Keycode key = pair.first;
        const Direction& dir = pair.second;

        if (getEngine()->isKeyPressed(key)) {

            m_direction = dir;

        }
    }
    updateAnimationFrame(iCurrentTime);

    // Check collision with zombies
    for (auto& id : ObjectIndexes::getZombieIndexes()) {
        // Get the player object

        Zombie* zb = dynamic_cast<Zombie*>(getEngine()->getDisplayableObject(id));
        if (zb == nullptr || zb->isDied()) continue;

        // Check if the zombie is colliding with the weapon
        if (Scyjz14CollisionDetection::checkPixel(getImage(), m_iCurrentFrameX * m_iDrawWidth, 0, m_iDrawWidth, m_iDrawHeight, getWeaponX(), getWeaponY(),
            zb->getImage(), zb->getCurrentFrameX() * zb->getDrawWidth(), zb->getDirection() * zb->getDrawHeight(), zb->getDrawWidth(), zb->getDrawHeight(), zb->getDrawingRegionLeft(), zb->getDrawingRegionTop()))
        {
            zb->lifeDecrease(1);
            if (zb->isDied()) {
                zb->checkIsLive();
                zb->drawBody();
                
                int timeDifference = abs(iCurrentTime - zb->getRevealingTime()) / 1000;  // Convert milliseconds to seconds
                int scoreIncrease = 5 + (100 / (timeDifference + 1));  // Base Score = 5, Max Time Bonus gradually decreases
                dynamic_cast<Scyjz14Engine*>(getEngine())->increaseScore(scoreIncrease);
            }
        }
    }

}

void Weapon::virtDraw() {
    if (isVisible()) {
        // Calculate the source position based on the current frame indices
        int iXSource = m_iCurrentFrameX * m_iDrawWidth;
        int iYSource = m_iCurrentFrameY * m_iDrawHeight;

        // Draw the current frame with transparency
        image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
            iXSource, iYSource,
            getWeaponX(),
            getWeaponY(),
            m_iDrawWidth, m_iDrawHeight);

    }
}