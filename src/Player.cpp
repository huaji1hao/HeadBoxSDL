#include "header.h"
#include "Player.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImageManager.h"


void Player::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible()) return;
	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP) || getEngine()->isKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed(SDLK_DOWN) || getEngine()->isKeyPressed(SDLK_s))
		m_iCurrentScreenY += 2;
	if (getEngine()->isKeyPressed(SDLK_LEFT) || getEngine()->isKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed(SDLK_RIGHT) || getEngine()->isKeyPressed(SDLK_d))
		m_iCurrentScreenX += 2;
	
	// If player is out of the window, move it back
	fixPosition();

	// If player is on a tile, change the tile
	if (m_pTileManager->isValidTilePosition(getXCentre(), getYCentre()))
	{
		{ // Max undates once per 60ms - prevents a lot of updates at once, helping to reduce load
			int iTileX = m_pTileManager->getMapXForScreenX(getXCentre());
			int iTileY = m_pTileManager->getMapYForScreenY(getYCentre());
			int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, (iCurrentTile + 1) % 3, getEngine(), getEngine()->getBackgroundSurface());
		}
	}

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
	m_iCurrentScreenX += 1.0 * k * dirX;
	m_iCurrentScreenY += 1.0 * k * dirY;
}