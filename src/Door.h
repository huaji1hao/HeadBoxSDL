#pragma once
#include "SpriteObject.h"
#include "State.h"

class Door :
    public SpriteObject
{
public:
    // Constructor
    Door(int xStart, int yStart, BaseEngine* pEngine, std::shared_ptr<State> targetState, std::string strURL = "resources/game/door.png")
        : SpriteObject(xStart, yStart, pEngine, strURL, 60, 71, true, true),
		m_targetState(targetState)
    {
    }

	void virtDraw() override;

	void virtDraw(int offSetX, int offSetY);

	void virtDoUpdate(int iCurrentTime) override;


protected:
	std::shared_ptr<State> m_targetState;  // Target state to switch to

	int getFrameCount() override {
		// Manually count that it is 8 for player
		return 2;
	}
};

