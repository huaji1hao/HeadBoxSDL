#include "header.h"
#include "SpriteObject.h"

void SpriteObject::virtDraw(){
	if (isVisible()) {
		// Calculate the source position based on the current frame indices
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		int iYSource = m_iCurrentFrameY * m_iDrawHeight;

		// Draw the current frame with transparency
		image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
			iXSource, iYSource,
			m_iCurrentScreenX + m_iStartDrawPosX,
			m_iCurrentScreenY + m_iStartDrawPosY,
			m_iDrawWidth, m_iDrawHeight);
	}
}


void AgentBaseObject::virtDraw(){
	if (isVisible()) {
		// Calculate the source position based on the current direction and frame index
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		// Assuming each direction is in a different row
		int iYSource = m_direction * m_iDrawHeight;

		// If any part of bottom is covered by the wall
		int bottomY = getDrawingRegionBottom();
		bool isLeftPassible = m_pTileManager->isPassable(getDrawingRegionLeft(), bottomY);
		bool isRightPassible = m_pTileManager->isPassable(getDrawingRegionRight(), bottomY);
		bool isCentrePassible = m_pTileManager->isPassable(getXCentre(), bottomY);

		if (!isLeftPassible || !isRightPassible || !isCentrePassible) {
			// Draw the image covered by the wall
			image.renderImageWithAlphaAndOverlay(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight, 0xEBDCC7);
		}
		else {
			// Draw the current frame with transparency
			image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}

	}
}

void AgentBaseObject::fixPosition() {
	DisplayableObject::fixPosition();

	/*int tileX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth / 2);
	int tileY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight / 2);
	int nextTileType = m_pTileManager->getMapValue(tileX, tileY);*/
	
	/*bool isLeftCentrePassible = m_pTileManager->isPassable(getXCentre() - 12, getYCentre() + 5);
	bool isRightCentrePassible = m_pTileManager->isPassable(getXCentre() + 12, getYCentre() + 5);
	bool isCentrePassible = m_pTileManager->isPassable(getXCentre(), getYCentre());*/


	if (!m_pTileManager->isPassableByObjectCentre(getXCentre(), getYCentre(), 12)) {

		// If next step is not passable, roll back to last position
		m_iCurrentScreenX = m_iPrevScreenX;
		m_iCurrentScreenY = m_iPrevScreenY;
	}
	else {
		// save the postion for rolling back
		m_iPrevScreenX = m_iCurrentScreenX;
		m_iPrevScreenY = m_iCurrentScreenY;
	}
}