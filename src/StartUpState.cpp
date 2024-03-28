#include "header.h"
#include "Zombie.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"

void StartUpState::virtSetupBackgroundBuffer(){
	eg->fillBackground(0x548746);
}

void StartUpState::virtDrawStringsUnderneath(){

}

void StartUpState::virtDrawStringsOnTop(){

}

void StartUpState::initialiseState(){
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();
	//eg->redrawDisplay();

	// Create array with default size for one object
	eg->createObjectArray(10);
	Button* button1 = new Button(400, 400, eg, "resources/cyan-button.png");
	button1->setLabel("Go to game", 50, 5);

	eg->storeObjectInArray(0, button1);
	eg->appendObjectToArray(new Button(400, 600, eg, "resources/cyan-button.png"));
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