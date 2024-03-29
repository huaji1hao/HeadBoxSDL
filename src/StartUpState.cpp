#include "header.h"
#include "Zombie.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"

void StartUpState::virtSetupBackgroundBuffer(){
	eg->fillBackground(0xffffff);
	Scyjz14Image title = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);
	DrawingSurface* surface = eg->getBackgroundSurface();
	//title.renderImageWithMask(surface, 0, 0, 150, 200, 400, 169, -1);
	title.renderImageWithAlpha(surface, 0, 0, 150, 50, 400, 169);


}

void StartUpState::virtDrawStringsUnderneath(){

}

void StartUpState::virtDrawStringsOnTop(){

}

void StartUpState::initialiseState(){
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(10);
	Button* button1 = new Button(280, 300, eg, "resources/cyan-button.png");
	button1->setLabel("Go to game", 5, 5);
	
	eg->storeObjectInArray(0, button1);
	eg->appendObjectToArray(new Button(280, 400, eg, "resources/cyan-button.png"));

}

void StartUpState::virtMouseDown(int iButton, int iX, int iY) {

}

void StartUpState::virtMouseUp(int iButton, int iX, int iY) {
	Button* button1 = dynamic_cast<Button*> (eg->getDisplayableObject(0));
	//if (button1->isInClickArea(iX, iY) && button1->getClickTimes() >= 0)
	if (button1->isInClickArea(iX, iY))
		eg->setState(new RunningState(eg));

}


StartUpState::~StartUpState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}