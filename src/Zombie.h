#pragma once
#include "ExampleObjects.h"
#include <vector>
#include "Player.h"
class Zombie :
    public ImageObject
{
public:
    Zombie(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
        , m_szLabel(NULL)
        , m_iXLabelOffset(0)
        , m_iYLabelOffset(0)
    {
    }
    Zombie(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, const char* label, int iXLabelOffset, int iYLabelOffset, bool useTopLeftFor00 = true, bool bVisible = true)
        : ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
        , m_szLabel(label)
        , m_iXLabelOffset(iXLabelOffset)
        , m_iYLabelOffset(iYLabelOffset)
    {

    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

private:
    // the function to attack all the player
    void attackPlayer();

    // the function to move the zombie by levy flight
    void levyFlight();

    void setLabel(char* label, int xOffset, int yOffset);

    // Label to apply
    const char* m_szLabel;
    // Label offset in pixels
    int m_iXLabelOffset;
    int m_iYLabelOffset;
};

