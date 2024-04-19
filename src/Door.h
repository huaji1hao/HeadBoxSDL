#pragma once
#include "SpriteObject.h"

class Door :
    public SpriteObject
{
public:
    // Constructor
    Door(int xStart, int yStart, BaseEngine* pEngine, std::string strURL = "resources/game/door.png")
        : SpriteObject(xStart, yStart, pEngine, strURL, 60, 71, true, true) 
    {
    }

	void virtDraw() override;

	void virtDraw(int offSetX, int offSetY);

	void virtDoUpdate(int iCurrentTime) override;


protected:
	int getFrameCount() override {
		// Manually count that it is 8 for player
		return 2;
	}
};

