#pragma once
#include "header.h"
#include "SpriteObject.h"
#include "Player.h"
#include "ObjectIndexes.h"


class Sword : public SpriteObject {
public:
    
    Sword(int xStart, int yStart, BaseEngine* pEngine, 
        std::string strURL = "resources/game/knife.png");

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
    // Get the weapon's x position
    int getWeaponX();
    // Get the weapon's y position
    int getWeaponY();

protected:
    int getFrameCount() override { return 8; }
    Direction m_direction = DOWN;
    Player* m_pPlayer = nullptr; // Pointer to the player
    int m_iDamage = 1; // Damage inflicted by the weapon
    int distance = 40; // Distance from the player
};

