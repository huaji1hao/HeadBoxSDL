#pragma once
#include "SpriteObject.h"
#include "Scyjz14TileManager.h"

class Player :
    public AgentBaseObject
{

public:
    Player(int xStart, int yStart, BaseEngine* pEngine, Scyjz14TileManager* pTileManager, std::string strURL = "resources/game/player/pistol.png",
        int frameWidth = 45, int frameHeight = 50, bool useTopLeftFor00 = true, bool bVisible = true)
        : AgentBaseObject(xStart, yStart, pEngine, strURL, frameWidth, frameHeight, useTopLeftFor00, bVisible)
    {
		m_pTileManager = pTileManager;
        m_direction = DOWN;
    }
    
    // when player is knocked away by enemy
    void knockedAway(int enemyX, int enemyY);

    void virtDoUpdate(int iCurrentTime) override;

	void checkTriggerMechanism(int x, int y);

	int getX() const { return m_iCurrentScreenX; }

	int getY() const { return m_iCurrentScreenY; }

    
protected:

	struct Movement {
		int dx, dy;
		Direction dir;
	};

	// Movement table
	const std::map<SDL_Keycode, Movement> movements{
		{ SDLK_w, { 0, -moving_speed, UP }},
		{ SDLK_s, { 0, moving_speed, DOWN }},
		{ SDLK_a, { -moving_speed, 0, LEFT }},
		{ SDLK_d, { moving_speed, 0, RIGHT }},
	};
};

