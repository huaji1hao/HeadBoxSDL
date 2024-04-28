#pragma once
#include "Scyjz14ImageManager.h"
class Button :
    public Scyjz14ImageObject
{
public:
    Button(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true);

    // Handle a key being pressed
    void virtMouseDown(int iButton, int iX, int iY);

    // Handle a key being released
    void virtMouseUp(int iButton, int iX, int iY);

    // Update the object
    void virtDoUpdate(int iCurrentTime) override;

    // Draw the object
    void virtDraw() override;

    // Get the number of times the button has been clicked
    int getClickTimes();

    // Check if the mouse is within the object
    bool isInClickArea();

    // Set the jump state of the button
    void setJumpState(bool isJump) { jumpState = isJump; }
    
    // Set the image when the mouse enters the object
    void setEnterImage(std::string strURL);

    // Use the top centre for (0,0) instead of the top left
    void useTopCentreFor00();

private:
    int clickTimes;
    bool isPressedWithin; // whether the mouse is pressed within the object
    int clickBias; // the bias of the click area
    bool jumpState;
    Scyjz14Image enter_image;
};
