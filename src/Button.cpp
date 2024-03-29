#include "header.h"
#include "Button.h"
#include "ExampleObjects.h"

bool Button::isInClickArea(int iX, int iY) {
	return virtIsPositionWithinObject(iX, iY);
}

void Button::virtMouseDown(int iButton, int iX, int iY) {
	// If the mouse is not within the object, return
	if(virtIsPositionWithinObject(iX, iY))
		setPosition(getDrawingRegionLeft(), getDrawingRegionTop() + 5);
	redrawDisplay();
}

void Button::virtMouseUp(int iButton, int iX, int iY) {
	// If the mouse is not within the object, return
	if (!virtIsPositionWithinObject(iX, iY)) return;
	// else increment clickTimes and move the button back to its original position
	clickTimes++;
	setPosition(getDrawingRegionLeft(), getDrawingRegionTop() - 5);
	redrawDisplay();
}

int Button::getClickTimes() {
	return clickTimes;
}

void Button::virtDraw()
{
	Scyjz14ImageObject::virtDraw();

	//char buf2[56];
	//sprintf(buf2, "Button has been clicked %d times", getClickTimes());
	//getEngine()->drawForegroundString(400, 350, buf2, 0xff00ff, getEngine()->getFont("resources/Truculenta-Regular.ttf", 24));
	
	if ((m_szLabel != nullptr) && (strlen(m_szLabel) > 0))
	{
		getEngine()->drawForegroundString(getDrawingRegionLeft() + m_iXLabelOffset, getDrawingRegionTop() + m_iYLabelOffset, m_szLabel, 0xffffff, getEngine()->getFont("resources/Truculenta-Regular.ttf", 24));
	}
	redrawDisplay();
}

void Button::setLabel(char* label, int xOffset, int yOffset) {
	m_szLabel = label;
	m_iXLabelOffset = xOffset;
	m_iYLabelOffset = yOffset;
}