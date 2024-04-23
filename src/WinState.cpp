#include "header.h"
#include "WinState.h"

#include "Zombie.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include "TextInputField.h"

WinState::WinState(Scyjz14Engine* engine)
	: State(engine)
	, m_iOffset(0)
	, leftSurface(engine)
	, rightSurface(engine)
{
	leftSurface.createSurface(eg->getWindowWidth(), eg->getWindowHeight());
	rightSurface.createSurface(eg->getWindowWidth(), eg->getWindowHeight());
}

void WinState::virtMainLoopDoBeforeUpdate() {
	int speed = 1; 
	m_iOffset = (m_iOffset + speed) % (2 * eg->getWindowWidth()); 
	eg->redrawDisplay(); 
}

void WinState::copyAllBackgroundBuffer() {
	DrawingSurface* foreground = eg->getForegroundSurface();
	int windowWidth = eg->getWindowWidth();
	int windowHeight = eg->getWindowHeight();

	if (m_iOffset <= windowWidth) {
		foreground->copyRectangleFrom(&leftSurface, 0, 0, windowWidth - m_iOffset, windowHeight, m_iOffset, 0);
		foreground->copyRectangleFrom(&rightSurface, windowWidth - m_iOffset, 0, m_iOffset, windowHeight, m_iOffset - windowWidth, 0);
	}
	else {
		foreground->copyRectangleFrom(&rightSurface, 0, 0, 2 * windowWidth - m_iOffset - 20, windowHeight, m_iOffset - windowWidth, 0);
		foreground->copyRectangleFrom(&leftSurface, 2 * windowWidth - m_iOffset, 0, m_iOffset - windowWidth, windowHeight, m_iOffset - 2 * windowWidth, 0);
	}

}

void WinState::virtSetupBackgroundBuffer() {
	Scyjz14Image backgroundImage = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	leftSurface.mySDLLockSurface();
	rightSurface.mySDLLockSurface();

	backgroundImage.renderImageWithAlpha(&leftSurface, 0, 0, 0, 0, eg->getWindowWidth(), eg->getWindowHeight());
	backgroundImage.renderImageWithAlpha(&rightSurface, eg->getWindowWidth() + 1, 0, 0, 0, eg->getWindowWidth(), eg->getWindowHeight());

	rightSurface.mySDLUnlockSurface();
	leftSurface.mySDLUnlockSurface();

}

void WinState::virtDrawStringsUnderneath() {

	// Print the string
	eg->drawForegroundString(50, 80, "Congratulations on escaping the zombie siege!",
		0xff0000, eg->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	// Build the string to print
	char buf[56];
	sprintf(buf, "Your score is %d", eg->getScore());

	eg->drawForegroundString(237, 150, buf, 0xff0000, eg->getFont("resources/Arial_Rounded_Bold.ttf", 36));
	
	Button* sendButton = dynamic_cast<Button*> (eg->getDisplayableObject(0));
	if (sendButton->getClickTimes() > 0) 
		eg->drawForegroundString(270, 350, "Send Successfully !",
			0x2bb280, eg->getFont("resources/Arial_Rounded_Bold.ttf", 20));
}

void WinState::virtDrawStringsOnTop() {

}

void WinState::initialiseStateObject() {
	eg->notifyObjectsAboutMouse(true);
	eg->notifyObjectsAboutKeys(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(5);
	Button* button1 = new Button(220, 310, eg, "resources/UI/SEND_SCORE_GREY.png");
	button1->setEnterImage("resources/UI/SEND_SCORE_BLACK.png");
	//button1->setJumpState(true);
	Button* button2 = new Button(280, 390, eg, "resources/UI/GO_BACK_GREY.png");
	button2->setEnterImage("resources/UI/GO_BACK_BLACK.png");
	button2->setJumpState(false);

	TextInputField* textField = new TextInputField(220, 240, 270, 40, eg, eg->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	eg->storeObjectInArray(0, button1);
	eg->storeObjectInArray(1, button2);
	eg->storeObjectInArray(2, textField);

}

void WinState::virtMouseUp(int iButton, int iX, int iY) {
	Button* sendButton = dynamic_cast<Button*> (eg->getDisplayableObject(0));

	if (sendButton->isInClickArea() && sendButton->getClickTimes() <= 0) {
		TextInputField* txf = dynamic_cast<TextInputField*> (eg->getDisplayableObject(2));
		std::string playerName = txf->getText(); // Method to get the name from input field

		if (playerName == "    <Enter Name>") {
			playerName = "unsung hero";
		}

		int score = eg->getScore(); // Method to get the current score
		saveScore(playerName, score); // Call the function to save the score
	}

	Button* backButton = dynamic_cast<Button*> (eg->getDisplayableObject(1));
	if (backButton->isInClickArea()) {
		eg->setState(std::make_shared<StartUpState>(eg));
	}
}

void WinState::saveScore(const std::string& name, int score) {
	std::ofstream outFile("resources/Score/leaderboard.txt", std::ios::app); // Open in append mode
	if (outFile) {
		outFile << name << "\t" << score << std::endl; // Use tab character as the delimiter
		outFile.close();
	}
	else {
		std::cerr << "Failed to open scores file." << std::endl;
	}

}



WinState::~WinState() {
	eg->clearScore();
	eg->destroyOldObjects(true);
	eg->clearContents();
}