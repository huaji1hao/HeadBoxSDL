#pragma once
#include "ExampleObjects.h"
class Button :
    public ImageObject
{
public:
    Button(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
    {
        clickTimes = 0;
    }

    // Handle a key being pressed
    void virtMouseDown(int iButton, int iX, int iY);
    // Handle a key being released
    void virtMouseUp(int iButton, int iX, int iY);
    // get click times
    int getClickTimes();
    // draw the button
    void virtDraw() override;

private:
    int clickTimes;
};
