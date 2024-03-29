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
        m_szLabel = nullptr;
        m_iXLabelOffset = 0;
        m_iYLabelOffset = 0;
    }

    // Handle a key being pressed
    void virtMouseDown(int iButton, int iX, int iY);
    // Handle a key being released
    void virtMouseUp(int iButton, int iX, int iY);
    // get click times
    int getClickTimes();
    bool isInClickArea(int iX, int iY);
    // draw the button
    void virtDraw() override;
    void setLabel(char* label, int xOffset, int yOffset);

private:
    int clickTimes;
    // Label to apply
    const char* m_szLabel;
    // Label offset in pixels
    int m_iXLabelOffset;
    int m_iYLabelOffset;
};
