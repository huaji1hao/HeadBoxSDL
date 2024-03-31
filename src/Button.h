#pragma once
#include "Scyjz14ImageManager.h"
class Button :
    public Scyjz14ImageObject
{
public:
    Button(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
        : Scyjz14ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
    {
        clickTimes = 0;
        clickBias = 5;
        m_szLabel = nullptr;
        m_iXLabelOffset = 0;
        m_iYLabelOffset = 0;
        jumpState = false;
    }

    // Handle a key being pressed
    void virtMouseDown(int iButton, int iX, int iY);
    // Handle a key being released
    void virtMouseUp(int iButton, int iX, int iY);
    // get click times
    int getClickTimes();
    bool isInClickArea();
    // draw the button
    void virtDraw() override;
    void setJumpState(bool isJump) { jumpState = isJump; }
    void setLabel(char* label, int xOffset, int yOffset);
    void virtDoUpdate(int iCurrentTime) override;

    void setEnterImage(std::string strURL) {
        enter_image = Scyjz14ImageManager::loadImage(strURL, true);
    }


private:
    int clickTimes;
    bool isPressedWithin = false;
    int clickBias;
    // Label to apply
    const char* m_szLabel;
    // Label offset in pixels
    int m_iXLabelOffset;
    int m_iYLabelOffset;
    bool jumpState;
    Scyjz14Image enter_image;
};
