#include "header.h"
#include "Button.h"
#include "ExampleObjects.h"

Button::Button(int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00, bool bVisible)
	: Scyjz14ImageObject(xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
{
	clickTimes = 0;
	clickBias = 5;
	jumpState = false;
	isPressedWithin = false;
}

bool Button::isInClickArea() {
	// If the mouse is within the object, return true
	return virtIsPositionWithinObject(getEngine()->getCurrentMouseX(), getEngine()->getCurrentMouseY());
}

void Button::virtMouseDown(int iButton, int iX, int iY) {
	// When the mouse is pressed down within the object, set the flag to true
	if (virtIsPositionWithinObject(iX, iY)) {
		isPressedWithin = true;
		
	}
}

void Button::virtMouseUp(int iButton, int iX, int iY) {
	// If the mouse is pressed up and within the object, increment the click times
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

	// If the jump state is true, move the object randomly
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
		// Draw the object with bias if the mouse is pressed within the object
		int yOffset = isPressedWithin ? clickBias : 0;
		if (enter_image.exists() && isInClickArea())
			enter_image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY + yOffset, m_iDrawWidth, m_iDrawHeight);
		else
		    image.renderImageWithAlpha(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY + yOffset, m_iDrawWidth, m_iDrawHeight);
	}
}

void Button::setEnterImage(std::string strURL) {
	enter_image = Scyjz14ImageManager::loadImage(strURL, true);
}

void Button::useTopCentreFor00() {
	m_iStartDrawPosX = -m_iDrawWidth / 2;
	m_iStartDrawPosY = 0;
}