#include "header.h"
#include "Button.h"
#include "ExampleObjects.h"

bool Button::isInClickArea() {
	return virtIsPositionWithinObject(getEngine()->getCurrentMouseX(), getEngine()->getCurrentMouseY());
}

void Button::virtMouseDown(int iButton, int iX, int iY) {
	// If the mouse is not within the object, return
	if (virtIsPositionWithinObject(iX, iY)) {
		isPressedWithin = true;
		
	}
		
	
}

void Button::virtMouseUp(int iButton, int iX, int iY) {
	// If the mouse is not within the object, return
	if (isPressedWithin && virtIsPositionWithinObject(iX, iY)) {
		clickTimes++;
		
	}
	isPressedWithin = false;
	
}

int Button::getClickTimes() {
	return clickTimes;
}

void Button::virtDoUpdate(int iCurrentTime) {
	if (!isVisible()) return;

	if (jumpState) {
		if (isInClickArea()) {
			m_iStartDrawPosX += rand() % 3 - 1;
			m_iStartDrawPosY += rand() % 3 - 1;

			if (abs(m_iStartDrawPosX) >= 5) m_iStartDrawPosX = 0;
			if (abs(m_iStartDrawPosY) >= 5) m_iStartDrawPosY = 0;
		}
		else {
			m_iStartDrawPosX = 0;
			m_iStartDrawPosY = 0;

		}
		
	}

	this->redrawDisplay();
	
};

void Button::virtDraw()
{
	if (isVisible())
	{
		int yOffset = isPressedWithin ? clickBias : 0;
		if (enter_image.exists() && isInClickArea())
			enter_image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY + yOffset, m_iDrawWidth, m_iDrawHeight);
		else
		    image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY + yOffset, m_iDrawWidth, m_iDrawHeight);
	}

	//char buf2[56];
	//sprintf(buf2, "Button has been clicked %d times", getClickTimes());
	//getEngine()->drawForegroundString(400, 350, buf2, 0xff00ff, getEngine()->getFont("resources/Truculenta-Regular.ttf", 24));
	
	if ((m_szLabel != nullptr) && (strlen(m_szLabel) > 0))
	{
		if (isInClickArea()) 
			getEngine()->drawForegroundString(getDrawingRegionLeft() + m_iXLabelOffset, getDrawingRegionTop() + m_iYLabelOffset, m_szLabel, 0xa6a6a6, getEngine()->getFont("resources/Arial_Rounded_Bold.ttf", 28));
		else
			getEngine()->drawForegroundString(getDrawingRegionLeft() + m_iXLabelOffset, getDrawingRegionTop() + m_iYLabelOffset, m_szLabel, 0x000000, getEngine()->getFont("resources/Arial_Rounded_Bold.ttf", 28));
	}


	
}

void Button::setLabel(char* label, int xOffset, int yOffset) {
	m_szLabel = label;
	m_iXLabelOffset = xOffset;
	m_iYLabelOffset = yOffset;
}