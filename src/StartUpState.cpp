#include "header.h"
#include "Zombie.h"
#include "Button.h"
#include "RunningState.h"
#include "LeaderBoardState.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include "InstructionState.h"
#include "ImagePixelMappingFlip.h"

void StartUpState::virtSetupBackgroundBuffer(){
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);
	Scyjz14Image photoFrame = Scyjz14ImageManager::loadImage("resources/background/photo_frame.png", true);
	DrawingSurface* surface = m_pEngine->getBackgroundSurface();
	
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
	photoFrame.renderImageWithAlpha(surface, 0, 0, 160, 30, 400, 219);

	Scyjz14Image pin = Scyjz14ImageManager::loadImage("resources/game/red_pin.png", true);

	pin.renderImageWithAlpha(surface, 0, 0, 550, 5, pin.getWidth(), pin.getHeight());

	ImagePixelMappingFlip flipMapper(ImagePixelMappingFlip::HORIZONTAL);
	pin.renderImageWithAlphaAndApplyingMapping(m_pEngine, surface, 0, 0, 150, 5, pin.getWidth(), pin.getHeight(), &flipMapper);
}


void StartUpState::initialiseStateObject(){
	m_pEngine->notifyObjectsAboutMouse(true);
	m_pEngine->notifyObjectsAboutKeys(false);
	m_pEngine->drawableObjectsChanged();

	m_pEngine->lockAndSetupBackground();

	// Create array with default size for one object
	m_pEngine->createObjectArray(10);
	Button* playButton = new Button(220, 290, m_pEngine, "resources/UI/SINGLE_PLAY_GREY.png");
	playButton->setEnterImage("resources/UI/SINGLE_PLAY_BLACK.png");
	playButton->setJumpState(true);

	Button* leaderBoardButton = new Button(220, 360, m_pEngine, "resources/UI/LEADERBOARDS_GREY.png");
	leaderBoardButton->setEnterImage("resources/UI/LEADERBOARDS_BLACK.png");

	Button* loadButton = new Button(360, 443, m_pEngine, "resources/UI/LOAD_STATE_GREY.png", false);
	loadButton->setEnterImage("resources/UI/LOAD_STATE_BLACK.png");

	Button* exitButton = new Button(360, 513, m_pEngine, "resources/UI/EXIT_GAME_GREY.png", false);
	exitButton->setEnterImage("resources/UI/EXIT_GAME_BLACK.png");


	m_pEngine->storeObjectInArray(0, playButton);
	m_pEngine->storeObjectInArray(1, leaderBoardButton);
	m_pEngine->storeObjectInArray(2, loadButton);
	m_pEngine->storeObjectInArray(3, exitButton);

}


void StartUpState::virtMouseUp(int iButton, int iX, int iY) {
	Button* playButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(0));
	Button* leaderBoardButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(1));
	Button* loadButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(2));
	Button* exitButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(3));

	// Check if the mouse is in the click area of the button
	if (playButton && playButton->isInClickArea()) {
		// Switch to next state
		m_pEngine->setState(std::make_shared<InstructionState>(m_pEngine));
		return;
	}

	if (leaderBoardButton && leaderBoardButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<LeaderBoardState>(m_pEngine));
		return;
	}

	if (loadButton && loadButton->isInClickArea()) {
		int loadLevel = determineLevelFromSaveFile("resources/game/game_state/my_state.txt");
		m_pEngine->setState(std::make_shared<RunningState>(m_pEngine, loadLevel, true));
		return;
	}

	if (exitButton && exitButton->isInClickArea()) {
		m_pEngine->setExitWithCode(0);
		return;
	}
		
}


StartUpState::~StartUpState() {
	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
}