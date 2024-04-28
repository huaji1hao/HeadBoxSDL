#pragma once
#include "SpriteObject.h"
#include "State.h"

class Door :
    public SpriteObject
{
public:
	// Set the target state to switch to when initialized
	Door(int xStart, int yStart, BaseEngine* pEngine, std::shared_ptr<State> targetState, std::string strURL = "resources/game/door.png");

	// Draw the object
	void virtDraw() override;

	// Draw the object with an offset
	void virtDraw(int offSetX, int offSetY);

	// Update the object
	void virtDoUpdate(int iCurrentTime) override;

protected:
	std::shared_ptr<State> m_targetState;  // Target state to switch to

	int getFrameCount() override {
		// Manually count that it is 2 for Door
		return 2;
	}
};

