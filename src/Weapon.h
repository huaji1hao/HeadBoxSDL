#pragma once
#include "header.h"
#include "SpriteObject.h"
#include "Player.h"
#include "ObjectIndexes.h"

class Weapon : public SpriteObject {
public:
    // Constructor
    Weapon(int xStart, int yStart, BaseEngine* pEngine, std::string strURL = "resources/game/knife.png")
        : SpriteObject(xStart, yStart, pEngine, strURL, 50, 50, true, true), m_iDamage(10) { // Damage inflicted by the weapon
        auto playerid = ObjectIndexes::getPlayerIndexes()[0];
        m_pPlayer = dynamic_cast<Player*>(getEngine()->getDisplayableObject(playerid));


        
    }

    const std::map<SDL_Keycode, Direction> movements{
        { SDLK_UP, UP},
        { SDLK_DOWN, DOWN},
        { SDLK_LEFT, LEFT},
        { SDLK_RIGHT, RIGHT},
    };


    // Update the weapon's position to float around the player
    void virtDoUpdate(int iCurrentTime) override {
        if (!isVisible())
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
        

        
    }

    // Draw the weapon
    void virtDraw() override {
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

    int getWeaponX() {
        if (m_direction == LEFT) return m_pPlayer->getDrawingRegionLeft() - distance;
        else if (m_direction == RIGHT) return m_pPlayer->getDrawingRegionLeft() + distance;
        else return m_pPlayer->getDrawingRegionLeft();
    }

    int getWeaponY() {
        if (m_direction == UP) return m_pPlayer->getDrawingRegionTop() - distance;
        else if (m_direction == DOWN) return m_pPlayer->getDrawingRegionTop() + distance;
        else return m_pPlayer->getDrawingRegionTop();
    }

    

protected:
    int getFrameCount() override { return 8; }
    Direction m_direction = DOWN;
    Player* m_pPlayer = nullptr; // Pointer to the player
    int m_iDamage; // Damage inflicted by the weapon
    int distance = 40;
};

