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
	DrawingSurface* surface = eg->getBackgroundSurface();
	
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
	photoFrame.renderImageWithAlpha(surface, 0, 0, 160, 30, 400, 219);

	Scyjz14Image pin = Scyjz14ImageManager::loadImage("resources/game/red_pin.png", true);

	pin.renderImageWithAlpha(surface, 0, 0, 550, 5, pin.getWidth(), pin.getHeight());

	ImagePixelMappingFlip flipMapper(ImagePixelMappingFlip::HORIZONTAL);
	pin.renderImageWithAlphaAndApplyingMapping(eg, surface, 0, 0, 150, 5, pin.getWidth(), pin.getHeight(), &flipMapper);
}


void StartUpState::initialiseStateObject(){
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(10);
	Button* playButton = new Button(220, 290, eg, "resources/UI/SINGLE_PLAY_GREY.png");
	playButton->setEnterImage("resources/UI/SINGLE_PLAY_BLACK.png");
	playButton->setJumpState(true);

	Button* leaderBoardButton = new Button(220, 360, eg, "resources/UI/LEADERBOARDS_GREY.png");
	leaderBoardButton->setEnterImage("resources/UI/LEADERBOARDS_BLACK.png");

	Button* loadButton = new Button(360, 443, eg, "resources/UI/LOAD_STATE_GREY.png", false);
	loadButton->setEnterImage("resources/UI/LOAD_STATE_BLACK.png");

	Button* exitButton = new Button(360, 513, eg, "resources/UI/EXIT_GAME_GREY.png", false);
	exitButton->setEnterImage("resources/UI/EXIT_GAME_BLACK.png");


	eg->storeObjectInArray(0, playButton);
	eg->storeObjectInArray(1, leaderBoardButton);
	eg->storeObjectInArray(2, loadButton);
	eg->storeObjectInArray(3, exitButton);

}


void StartUpState::virtMouseUp(int iButton, int iX, int iY) {
	Button* playButton = dynamic_cast<Button*> (eg->getDisplayableObject(0));
	Button* leaderBoardButton = dynamic_cast<Button*> (eg->getDisplayableObject(1));
	Button* loadButton = dynamic_cast<Button*> (eg->getDisplayableObject(2));
	Button* exitButton = dynamic_cast<Button*> (eg->getDisplayableObject(3));

	// Check if the mouse is in the click area of the button
	if (playButton && playButton->isInClickArea()) {
		// Switch to next state
		eg->setState(std::make_shared<InstructionState>(eg));
		return;
	}

	if (leaderBoardButton && leaderBoardButton->isInClickArea()) {
		eg->setState(std::make_shared<LeaderBoardState>(eg));
		return;
	}

	if (loadButton && loadButton->isInClickArea()) {
		int loadLevel = determineLevelFromSaveFile("resources/game/game_state/my_state.txt");
		eg->setState(std::make_shared<RunningState>(eg, loadLevel, true));
		return;
	}

	if (exitButton && exitButton->isInClickArea()) {
		eg->setExitWithCode(0);
		return;
	}
		
}


StartUpState::~StartUpState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}