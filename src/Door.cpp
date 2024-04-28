#include "header.h"
#include "Door.h"
#include "ObjectIndexes.h"
#include "Zombie.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "Scyjz14CollisionDetection.h"

Door::Door(int xStart, int yStart, BaseEngine* pEngine, std::shared_ptr<State> targetState, std::string strURL)
	: SpriteObject(xStart, yStart, pEngine, strURL, 60, 71, true, true),
	m_targetState(targetState)
{
}


void Door::virtDraw(){
	if (isVisible()) {
		// Calculate the source position based on the current frame indices
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		int iYSource = m_iCurrentFrameY * m_iDrawHeight;

		m_pEngine->lockBackgroundForDrawing();

		// Draw the current frame with transparency
		image.renderImageWithAlpha(getEngine()->getBackgroundSurface(),
			iXSource, iYSource,
			m_iCurrentScreenX + m_iStartDrawPosX,
			m_iCurrentScreenY + m_iStartDrawPosY,
			m_iDrawWidth, m_iDrawHeight);

		m_pEngine->unlockBackgroundForDrawing();
	}
}

void Door::virtDraw(int offSetX, int offSetY) {
	if (isVisible()) {
		// Calculate the source position based on the current frame indices
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		int iYSource = m_iCurrentFrameY * m_iDrawHeight;

		m_pEngine->lockBackgroundForDrawing();

		// Draw the current frame with transparency
		image.renderImageWithAlpha(getEngine()->getBackgroundSurface(),
			iXSource, iYSource,
			m_iCurrentScreenX + m_iStartDrawPosX + offSetX,
			m_iCurrentScreenY + m_iStartDrawPosY + offSetY,
			m_iDrawWidth, m_iDrawHeight);

		m_pEngine->unlockBackgroundForDrawing();
	}
}

void Door::virtDoUpdate(int iCurrentTime){
	// When all the zombies died
	bool isAllZombiesDead = true;
	for (auto index : ObjectIndexes::getZombieIndexes()) {
		Zombie* zb = dynamic_cast<Zombie*>(m_pEngine->getDisplayableObject(index));
		if (!zb->isDied()) {
			isAllZombiesDead = false;
			break;
		}
	}

	// If all the zombies are dead, 
	// check if the player is colliding with the door
	if (isAllZombiesDead) {
		// Open the door
		setCurrentFrame(1, 0);

		Player* player = dynamic_cast<Player*>(getEngine()->getDisplayableObject(ObjectIndexes::getPlayerIndexes()[0]));

		// When the player is in the door, switch to the target state
		if (Scyjz14CollisionDetection::checkPixelIsImg2InImg1(getImage(), m_iCurrentFrameX * m_iDrawWidth, 0, m_iDrawWidth, m_iDrawHeight, getDrawingRegionLeft(), getDrawingRegionTop(),
			player->getImage(), player->getCurrentFrameX() * player->getDrawWidth(), player->getDirection() * player->getDrawHeight(), player->getDrawWidth(), player->getDrawHeight(), player->getDrawingRegionLeft(), player->getDrawingRegionTop()))
		{
			Scyjz14Engine* eg = dynamic_cast<Scyjz14Engine*>(m_pEngine);
			eg->setState(m_targetState);
		}

	}
}
