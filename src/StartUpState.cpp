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

void StartUpState::virtSetupBackgroundBuffer(){
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);
	Scyjz14Image title = Scyjz14ImageManager::loadImage("resources/background/menu_title.png", true);
	DrawingSurface* surface = eg->getBackgroundSurface();
	//title.renderImageWithMask(surface, 0, 0, 150, 200, 400, 169, -1);
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
	title.renderImageWithAlpha(surface, 0, 0, 150, 20, 400, 169);

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
	Button* button1 = new Button(220, 280, eg, "resources/UI/SINGLE_PLAY_GREY.png");
	button1->setEnterImage("resources/UI/SINGLE_PLAY_BLACK.png");
	button1->setJumpState(true);

	Button* button2 = new Button(220, 360, eg, "resources/UI/INSTRUCTIONS_GREY.png");
	button2->setEnterImage("resources/UI/INSTRUCTIONS_BLACK.png");

	Button* button3 = new Button(220, 440, eg, "resources/UI/LEADERBOARDS_GREY.png");
	button3->setEnterImage("resources/UI/LEADERBOARDS_BLACK.png");

	eg->storeObjectInArray(0, button1);
	eg->storeObjectInArray(1, button2);
	eg->storeObjectInArray(2, button3);
	//eg->appendObjectToArray(new Button(220, 360, eg, "resources/UI/INSTRUCTIONS_GREY.png"));

}

void StartUpState::virtMouseDown(int iButton, int iX, int iY) {

}

void StartUpState::virtMouseUp(int iButton, int iX, int iY) {
	Button* button1 = dynamic_cast<Button*> (eg->getDisplayableObject(0));
	Button* button2 = dynamic_cast<Button*> (eg->getDisplayableObject(1));
	Button* button3 = dynamic_cast<Button*> (eg->getDisplayableObject(2));

	if (button1 && button1->isInClickArea()) {
		eg->setState(std::make_shared<RunningState>(eg));
		return;
	}

	if (button2 && button2->isInClickArea()) {
		eg->setState(std::make_shared<InstructionState>(eg));
		return;
	}

	if (button3 && button3->isInClickArea()) {
		eg->setState(std::make_shared<LeaderBoardState>(eg));
		return;
	}
		
}


StartUpState::~StartUpState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}