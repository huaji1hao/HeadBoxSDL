#pragma once
#include "header.h"
#include "Scyjz14ImageManager.h"
#include "Scyjz14TileManager.h"

class SpriteObject : public Scyjz14ImageObject {
public:

	// Define an enumeration for the directions the sprite object can face
	enum Direction {
		UP, DOWN, LEFT, RIGHT,
		UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT
	};

	// Constructor to initialize the sprite object with a sprite sheet URL and frame dimensions
	SpriteObject(int xStart, int yStart, BaseEngine* pEngine,
		const std::string& strURL, int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true);

	// Override virtDraw to render the current frame of the sprite sheet
	virtual void virtDraw() override;

	// Function to set the current frame based on the sprite sheet
	void setCurrentFrame(int frameX, int frameY) {
		m_iCurrentFrameX = frameX;
		m_iCurrentFrameY = frameY;
	}

	void setFrameRate(int frameRate) {
		// A second can have 1000ms / frameRate frams
		// defult is 10 fps
		m_iTimeBetweenFrames = 1000 / frameRate;
	}

	int getCurrentFrameX() { return m_iCurrentFrameX; }

	int getCurrentFrameY() { return m_iCurrentFrameY; }

protected:
	// Function to update the animation frame based on the elapsed time
	virtual void updateAnimationFrame(int iCurrentTime);

	// Helper function to get the frame count based on the sprite sheet and direction
	// Assuming that the frame count is the same for all directions
	// and that all frames are evenly spaced in the sprite sheet
	virtual int getFrameCount() = 0;

	int m_iTimeBetweenFrames = 100; // Time between frames in milliseconds
	int m_iLastUpdateTime = 0; // Last time the frame was updated

	int m_iCurrentFrameX = 0;  // X index of the current frame
	int m_iCurrentFrameY = 0;  // Y index of the current frame
};


class AgentBaseObject : public SpriteObject {
public:
	// Agent is a sprite object that can move and has a direction
	AgentBaseObject(int xStart, int yStart, BaseEngine* pEngine, 
		const std::string& strURL, int frameWidth, int frameHeight,
		bool useTopLeftFor00 = true, bool bVisible = true, int revealTime = 0);

	// Function to draw the Agent
	virtual void virtDraw() override;
	// Function to make show the agent cannot pass the wall
	virtual void fixPosition();
	// Function get the direction of the agent
	Direction getDirection() { return m_direction; }
	// Function to set the speed of the agent
	void setSpeed(int speed) { moving_speed = speed; }
	// Function to get the life value of the agent
	int getLifeValue() { return lifeValue; }
	// Function to set the life value of the agent
	void setLifeValue(int life) { lifeValue = life; }
	// FUnction to decrease the life value of the agent, the value cannot be negative
	void lifeDecrease(int value);
	// Function to get if the agent is died
	bool isDied() { return lifeValue <= 0; }
	// Function to check if the agent is still alive
	void checkIsLive() { if (isDied()) setVisible(false); }
	// Function to set the appearance time of the agent
	void setRevealingTime(int timeStamp) { revealingTime = timeStamp; }
	// Function to get the appearance time of the agent
	int getRevealingTime() { return revealingTime; }

protected:
	Direction m_direction = UP; // Current direction the object faces
	int moving_speed = 2; // Speed of the object
	int m_iPrevScreenX = 0; // Previous screen X position
	int m_iPrevScreenY = 0; // Previous screen Y position
	int widthOffset = 12; // Width offset from the center of the object
	int lifeValue = 100;  // Life value of the agent
	int revealingTime = 0; // Appearance time of the agent
	Scyjz14TileManager* m_pTileManager = nullptr;
	Scyjz14Image health_bar = nullptr; // Health bar image

	virtual int getFrameCount() override {
		// Manually count that it is 8 for all agents
		return 8;
	}

};

