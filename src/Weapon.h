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
    void virtDoUpdate(int iCurrentTime) override;

    // Draw the weapon
    void virtDraw() override;

    int getWeaponX();

    int getWeaponY();

protected:
    int getFrameCount() override { return 8; }
    Direction m_direction = DOWN;
    Player* m_pPlayer = nullptr; // Pointer to the player
    int m_iDamage; // Damage inflicted by the weapon
    int distance = 40;
};

