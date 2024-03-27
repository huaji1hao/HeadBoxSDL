#include "header.h"
#include "Button.h"
#include "ExampleObjects.h"

void Button::virtMouseDown(int iButton, int iX, int iY) {
	if (!isVisible()) return;
	// If the mouse is not within the object, return
	if(virtIsPositionWithinObject(iX, iY))
		setPosition(getDrawingRegionLeft(), getDrawingRegionTop() + 5);
}

void Button::virtMouseUp(int iButton, int iX, int iY) {
	if (!isVisible()) return;
	// If the mouse is not within the object, return
	if (!virtIsPositionWithinObject(iX, iY)) return;
	// else increment clickTimes and move the button back to its original position
	clickTimes++;
	setPosition(getDrawingRegionLeft(), getDrawingRegionTop() - 5);
}

int Button::getClickTimes() {
	return clickTimes;
}

void Button::virtDraw()
{
	ImageObject::virtDraw();
	char buf2[56];
	sprintf(buf2, "Button has been clicked %d times", getClickTimes());
	getEngine()->drawForegroundString(400, 350, buf2, 0xff00ff, getEngine()->getFont("resources/Truculenta-Regular.ttf", 24));
}