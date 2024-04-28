#include "header.h"
#include "LoseState.h"

#include "Zombie.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include "TextInputField.h"
#include "RunningState.h"

// Constructor
LoseState::LoseState(Scyjz14Engine* engine) 
	: State(engine)
	, numSurfaces(5)
	, m_iSwitchThreshold(10)
	, m_iSwitchCounter(m_iSwitchThreshold - 1) 
{
	// Resize the vector to hold all required surfaces
	m_surfaces.resize(numSurfaces, DrawingSurface(engine));

	for (auto& surface : m_surfaces) {
		surface.createSurface(m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());
	}
}

void LoseState::virtMainLoopDoBeforeUpdate() {
	// use this switch logic to speed down the switch speed
	m_iSwitchCounter++;
	// only whenthe conter achieve the threshold then the background can be changed
	if (m_iSwitchCounter >= m_iSwitchThreshold) {
		// We change which surface is being used for the background each time through the loop.
		m_iCurrentSurfaceNumber = (m_iCurrentSurfaceNumber + 1) % numSurfaces;
		m_pEngine->setBackgroundSurface(&m_surfaces[m_iCurrentSurfaceNumber]);
		m_pEngine->redrawDisplay(); // Force redraw to copy background again
		m_iSwitchCounter = 0;// reset the counter
	}

}

void LoseState::virtSetupBackgroundBuffer() {
	// Load images
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);
	std::vector<Scyjz14Image> playerImages = {
		Scyjz14ImageManager::loadImage("resources/game/player/died0.png", true),
		Scyjz14ImageManager::loadImage("resources/game/player/died1.png", true),
		Scyjz14ImageManager::loadImage("resources/game/player/died2.png", true),
		Scyjz14ImageManager::loadImage("resources/game/player/died3.png", true),
		Scyjz14ImageManager::loadImage("resources/game/player/died4.png", true),
	};

	// Coordinates and sizes for drawing
	int imageX = 280, imageY = 114, imgSize = 150;

	// Render images to each surface
	for (int i = 0; i < numSurfaces; i++) {
		m_surfaces[i].mySDLLockSurface();

		background.renderImageWithAlpha(&m_surfaces[i], 150, 0, 0, 0, 720, 560);
		if (i < playerImages.size()) {
			playerImages[i].renderImageWithAlpha(&m_surfaces[i], 0, 0, imageX, imageY, imgSize, imgSize);
		}

		// Build the string to print
		char buf[56];
		sprintf(buf, "Your score is %d", m_pEngine->getScore());

		m_surfaces[i].drawScalableString(260, 55, "You died",
			0xff0000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 48));
		m_surfaces[i].drawScalableString(237, 280, buf, 
			0xff0000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 36));

		m_surfaces[i].mySDLUnlockSurface();
	}
}

void LoseState::initialiseStateObject() {
	m_pEngine->notifyObjectsAboutMouse(true);
	m_pEngine->drawableObjectsChanged();

	m_pEngine->lockAndSetupBackground();

	// Create array with default size for one object
	m_pEngine->createObjectArray(5);
	Button* button1 = new Button(265, 360, m_pEngine, "resources/UI/TRY_AGAIN_GREY.png");
	button1->setEnterImage("resources/UI/TRY_AGAIN_BLACK.png");
	
	Button* button2 = new Button(280, 440, m_pEngine, "resources/UI/GO_BACK_GREY.png");
	button2->setEnterImage("resources/UI/GO_BACK_BLACK.png");

	m_pEngine->storeObjectInArray(0, button1);
	m_pEngine->storeObjectInArray(1, button2);
}

void LoseState::virtMouseUp(int iButton, int iX, int iY) {
	Button* tryAgainButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(0));
	Button* goBackButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(1));

	if (tryAgainButton && tryAgainButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<RunningState>(m_pEngine));
		return;
	}

	if (goBackButton && goBackButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<StartUpState>(m_pEngine));
		return;
	}
}

LoseState::~LoseState() {
	m_pEngine->clearScore();
	m_pEngine->resetBackgroundSurface();
	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
}