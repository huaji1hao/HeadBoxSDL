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
	Scyjz14Image title = Scyjz14ImageManager::loadImage("resources/background/photo_frame.png", true);
	DrawingSurface* surface = eg->getBackgroundSurface();
	//title.renderImageWithMask(surface, 0, 0, 150, 200, 400, 169, -1);
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
	title.renderImageWithAlpha(surface, 0, 0, 160, 30, 400, 219);

	Scyjz14Image pin = Scyjz14ImageManager::loadImage("resources/game/red_pin.png", true);

	pin.renderImageWithAlpha(surface, 0, 0, 550, 5, pin.getWidth(), pin.getHeight());

	ImagePixelMappingFlip flipMapper(ImagePixelMappingFlip::HORIZONTAL);
	pin.renderImageWithAlphaAndApplyingMapping(eg, surface, 0, 0, 150, 5, pin.getWidth(), pin.getHeight(), &flipMapper);


}

void StartUpState::virtDrawStringsUnderneath(){

}

void StartUpState::virtDrawStringsOnTop(){

}

void StartUpState::initialiseStateObject(){
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(10);
	Button* button1 = new Button(220, 290, eg, "resources/UI/SINGLE_PLAY_GREY.png");
	button1->setEnterImage("resources/UI/SINGLE_PLAY_BLACK.png");
	button1->setJumpState(true);

	Button* button2 = new Button(220, 360, eg, "resources/UI/LEADERBOARDS_GREY.png");
	button2->setEnterImage("resources/UI/LEADERBOARDS_BLACK.png");

	Button* button3 = new Button(360, 443, eg, "resources/UI/LOAD_STATE_GREY.png", false);
	button3->setEnterImage("resources/UI/LOAD_STATE_BLACK.png");

	Button* button4 = new Button(360, 513, eg, "resources/UI/EXIT_GAME_GREY.png", false);
	button4->setEnterImage("resources/UI/EXIT_GAME_BLACK.png");


	eg->storeObjectInArray(0, button1);
	eg->storeObjectInArray(1, button2);
	eg->storeObjectInArray(2, button3);
	eg->storeObjectInArray(3, button4);

}

void StartUpState::virtMouseDown(int iButton, int iX, int iY) {

}

void StartUpState::virtMouseUp(int iButton, int iX, int iY) {
	Button* button1 = dynamic_cast<Button*> (eg->getDisplayableObject(0));
	Button* button2 = dynamic_cast<Button*> (eg->getDisplayableObject(1));
	Button* button3 = dynamic_cast<Button*> (eg->getDisplayableObject(2));
	Button* button4 = dynamic_cast<Button*> (eg->getDisplayableObject(3));

	if (button1 && button1->isInClickArea()) {
		eg->setState(std::make_shared<InstructionState>(eg));
		return;
	}

	if (button2 && button2->isInClickArea()) {
		eg->setState(std::make_shared<LeaderBoardState>(eg));
		return;
	}

	if (button3 && button3->isInClickArea()) {
		int loadLevel = determineLevelFromSaveFile("resources/game/game_state/my_state.txt");
		eg->setState(std::make_shared<RunningState>(eg, loadLevel, true));
		return;
	}

	if (button4 && button4->isInClickArea()) {
		eg->setExitWithCode(0);
		return;
	}
		
}


StartUpState::~StartUpState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}