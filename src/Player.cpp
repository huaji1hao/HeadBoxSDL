#include "header.h"
#include "Player.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImageManager.h"
#include "Scyjz14Engine.h"
#include "LoseState.h"

void Player::checkTriggerMechanism(int x, int y) {
	if (m_pTileManager->isValidTilePosition(x, y))
	{
		int iTileX = m_pTileManager->getMapXForScreenX(x);
		int iTileY = m_pTileManager->getMapYForScreenY(y);

		int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);

		if (iCurrentTile == Scyjz14TileManager::MECHANISM) {
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, Scyjz14TileManager::NONE, getEngine(), getEngine()->getBackgroundSurface());
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, Scyjz14TileManager::MECHANISM_PRESSED, getEngine(), getEngine()->getBackgroundSurface());
			
			
			m_pTileManager->setAndRedrawMapValueAt(12, 5, Scyjz14TileManager::WALL7, getEngine(), getEngine()->getBackgroundSurface());
			m_pTileManager->setAndRedrawMapValueAt(11, 6, Scyjz14TileManager::WALL7, getEngine(), getEngine()->getBackgroundSurface());
			m_pTileManager->setAndRedrawMapValueAt(13, 6, Scyjz14TileManager::WALL7, getEngine(), getEngine()->getBackgroundSurface());
			m_pTileManager->setAndRedrawMapValueAt(12, 7, Scyjz14TileManager::WALL7, getEngine(), getEngine()->getBackgroundSurface());

		}
		
	}
}

void Player::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible() || getEngine()->isPaused()) return;
	
	// Handle key inputs to update position and direction

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
	checkTriggerMechanism(getXCentre() - widthOffset, getYCentre() + 10);
	checkTriggerMechanism(getXCentre() + widthOffset, getYCentre() + 10);

	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();

	/*Scyjz14Engine* eg = dynamic_cast<Scyjz14Engine*>(m_pEngine);
	eg->setState(std::make_shared<WinState>(eg));*/

	if (isDied()) {
		Scyjz14Engine* eg = dynamic_cast<Scyjz14Engine*>(m_pEngine);
		eg->setState(std::make_shared<LoseState>(eg));
	}
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

	lifeDecrease(5);
}