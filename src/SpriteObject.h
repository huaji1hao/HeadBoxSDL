#pragma once
#include "header.h"
#include "Scyjz14ImageManager.h"
#include "Scyjz14TileManager.h"

class SpriteObject : public Scyjz14ImageObject {
public:
	// Constructor to initialize the sprite object with a sprite sheet URL and frame dimensions

	SpriteObject(int xStart, int yStart, BaseEngine* pEngine, const std::string& strURL,
		int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true)
		: Scyjz14ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible) {

		// Assuming that the sprite sheet's individual frame size is the same as the object's drawing size
		m_iDrawWidth = frameWidth;
		m_iDrawHeight = frameHeight;
	}


	// Override virtDraw to render the current frame of the sprite sheet
	virtual void virtDraw() override {
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

	// Function to set the current frame based on the sprite sheet
	void setCurrentFrame(int frameX, int frameY) {
		m_iCurrentFrameX = frameX;
		m_iCurrentFrameY = frameY;
	}

	void setFrameRate(int frameRate) {
		// A second can have 1000ms / frameRate frams
		m_iTimeBetweenFrames = 1000 / frameRate;
	}

protected:
	// Function to update the animation frame based on the elapsed time
	virtual void updateAnimationFrame(int iCurrentTime) {
		// Calculate the time elapsed since the last frame update
		int iElapsedTime = iCurrentTime - m_iLastUpdateTime;

		// Check if it is time to update the frame
		if (iElapsedTime >= m_iTimeBetweenFrames) {
			// Update the frame index
			m_iCurrentFrameX = (m_iCurrentFrameX + 1) % getFrameCount();
			// Reset the last update time
			m_iLastUpdateTime = iCurrentTime;
		}
	}

	// Helper function to get the frame count based on the sprite sheet and direction
	// Assuming that the frame count is the same for all directions
	// and that all frames are evenly spaced in the sprite sheet
	virtual int getFrameCount() = 0;

	int m_iTimeBetweenFrames = 100; // Time between frames in milliseconds
	int m_iLastUpdateTime = 0; // Last time the frame was updated

	int m_iCurrentFrameX = 0;  // X index of the current frame
	int m_iCurrentFrameY = 0;;  // Y index of the current frame
};

class AgentBaseObject : public SpriteObject {
public:

	// Define an enumeration for the directions the sprite object can face
	enum Direction {
		UP, DOWN, LEFT, RIGHT,
		UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT
	};

	AgentBaseObject(int xStart, int yStart, BaseEngine* pEngine, const std::string& strURL,
		int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true)
		: SpriteObject(xStart, yStart, pEngine, strURL, frameWidth, frameHeight, useTopLeftFor00, bVisible) {
		m_direction = UP; // Default direction
		m_pTileManager = nullptr;
	}

	// Function to draw the Agent
	virtual void virtDraw() override {
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

	void setSpeed(int speed) { moving_speed = speed; }

	void fixPosition() {
		DisplayableObject::fixPosition();
		
		int tileX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth / 2);
		int tileY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight / 2);
		int nextTileType = m_pTileManager->getMapValue(tileX, tileY);


		if (!m_pTileManager->isPassable(nextTileType)) {

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


protected:
	Direction m_direction; // Current direction the object faces
	int moving_speed = 2;
	int m_iPrevScreenX = 0;
	int m_iPrevScreenY = 0;
	bool sig_redrawWall = false;
	Scyjz14TileManager* m_pTileManager;

	virtual int getFrameCount() override {
		// Manually count that it is 8 for player
		return 8;
	}

};
