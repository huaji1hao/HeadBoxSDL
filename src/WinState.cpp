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
	leftSurface.createSurface(m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());
	rightSurface.createSurface(m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());
}

void WinState::virtMainLoopDoBeforeUpdate() {
	// Update the background offset
	int speed = 1; 
	m_iOffset = (m_iOffset + speed) % (2 * m_pEngine->getWindowWidth()); 
	m_pEngine->redrawDisplay(); 
}

void WinState::copyAllBackgroundBuffer() {
	DrawingSurface* foreground = m_pEngine->getForegroundSurface();
	int windowWidth = m_pEngine->getWindowWidth();
	int windowHeight = m_pEngine->getWindowHeight();

	// Make the background scroll
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
	// Read the background images
	Scyjz14Image backgroundImage = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	leftSurface.mySDLLockSurface();
	rightSurface.mySDLLockSurface();

	backgroundImage.renderImageWithAlpha(&leftSurface, 0, 0, 0, 0, m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());
	backgroundImage.renderImageWithAlpha(&rightSurface, m_pEngine->getWindowWidth() + 1, 0, 0, 0, m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());

	rightSurface.mySDLUnlockSurface();
	leftSurface.mySDLUnlockSurface();

}

void WinState::virtDrawStringsUnderneath() {
	// Print the string
	m_pEngine->drawForegroundString(50, 80, "Congratulations on escaping the zombie siege!",
		0xff0000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	// Build the string to print
	char buf[56];
	sprintf(buf, "Your score is %d", m_pEngine->getScore());

	m_pEngine->drawForegroundString(237, 150, buf, 0xff0000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 36));
	
	Button* sendButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(0));
	if (sendButton->getClickTimes() > 0) 
		m_pEngine->drawForegroundString(270, 350, "Send Successfully !",
			0x2bb280, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 20));
}

void WinState::initialiseStateObject() {
	m_pEngine->notifyObjectsAboutMouse(true);
	m_pEngine->notifyObjectsAboutKeys(true);
	m_pEngine->drawableObjectsChanged();

	m_pEngine->lockAndSetupBackground();

	// Create array with default size for one object
	m_pEngine->createObjectArray(5);
	Button* sendScoreButton = new Button(220, 310, m_pEngine, "resources/UI/SEND_SCORE_GREY.png");
	sendScoreButton->setEnterImage("resources/UI/SEND_SCORE_BLACK.png");
	
	Button* goBackButton = new Button(280, 390, m_pEngine, "resources/UI/GO_BACK_GREY.png");
	goBackButton->setEnterImage("resources/UI/GO_BACK_BLACK.png");
	goBackButton->setJumpState(false);

	TextInputField* textField = new TextInputField(220, 240, 270, 40, m_pEngine, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	m_pEngine->storeObjectInArray(0, sendScoreButton);
	m_pEngine->storeObjectInArray(1, goBackButton);
	m_pEngine->storeObjectInArray(2, textField);

}

void WinState::virtMouseUp(int iButton, int iX, int iY) {
	Button* sendButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(0));

	if (sendButton->isInClickArea() && sendButton->getClickTimes() <= 0) {
		TextInputField* txf = dynamic_cast<TextInputField*> (m_pEngine->getDisplayableObject(2));
		std::string playerName = txf->getText(); // Method to get the name from input field

		if (playerName == "    <Enter Name>") {
			playerName = "unsung hero";
		}

		int score = m_pEngine->getScore(); // Method to get the current score
		saveScore(playerName, score); // Call the function to save the score
	}

	Button* backButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(1));
	if (backButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<StartUpState>(m_pEngine));
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
	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
}