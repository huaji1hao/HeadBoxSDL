#include "header.h"
#include "Player.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImageManager.h"


void Player::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible()) return;
	
	// Handle key inputs to update position and direction
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

		{ SDLK_UP, { 0, -moving_speed, UP }},
		{ SDLK_DOWN, { 0, moving_speed, DOWN }},
		{ SDLK_LEFT, { -moving_speed, 0, LEFT }},
		{ SDLK_RIGHT, { moving_speed, 0, RIGHT }},
	};

	for (const auto& pair : movements) {
		SDL_Keycode key = pair.first;
		const Movement& movement = pair.second;

		if (getEngine()->isKeyPressed(key)) {
			m_iCurrentScreenX += movement.dx;
			m_iCurrentScreenY += movement.dy;
			m_direction = movement.dir;
			updateAnimationFrame(iCurrentTime);
			break; //only process one key
		}
	}

	// If player is out of the window, move it back
	fixPosition();

	// If player is on a tile, change the tile
	//if (m_pTileManager->isValidTilePosition(getXCentre(), getYCentre()))
	//{
	//	{ // Max undates once per 60ms - prevents a lot of updates at once, helping to reduce load
	//		int iTileX = m_pTileManager->getMapXForScreenX(getXCentre());
	//		int iTileY = m_pTileManager->getMapYForScreenY(getYCentre());
	//		int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);
	//		m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, (iCurrentTile + 1) % 3, getEngine(), getEngine()->getBackgroundSurface());
	//	}
	//}

	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}

void Player::knockedAway(int enemyX, int enemyY) {
	// Calculate the direction vector from enemy to player
	int dirX = getXCentre() - enemyX;
	int dirY = getYCentre() - enemyY;

	// A constant to scale the direction vector
	double k = 0.5;
	
	// Calculate new position
	m_iCurrentScreenX += static_cast<int> (k * dirX);
	m_iCurrentScreenY += static_cast<int> (k * dirY);
}