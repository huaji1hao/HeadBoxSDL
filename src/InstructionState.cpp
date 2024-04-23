#include "header.h"
#include "InstructionState.h"

#include "Zombie.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include "TextInputField.h"
#include "RunningState.h"

void InstructionState::virtMainLoopDoBeforeUpdate() {
	

}

void InstructionState::virtDrawStringsUnderneath() {

}

void InstructionState::virtDrawStringsOnTop() {

}

void InstructionState::virtSetupBackgroundBuffer() {

	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	DrawingSurface* surface = eg->getBackgroundSurface();
	//title.renderImageWithMask(surface, 0, 0, 150, 200, 400, 169, -1);
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
}

void InstructionState::initialiseStateObject() {
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(5);
	Button* button1 = new Button(265, 360, eg, "resources/UI/TRY_AGAIN_GREY.png");
	button1->setEnterImage("resources/UI/TRY_AGAIN_BLACK.png");

	Button* button2 = new Button(280, 440, eg, "resources/UI/GO_BACK_GREY.png");
	button2->setEnterImage("resources/UI/GO_BACK_BLACK.png");

	eg->storeObjectInArray(0, button1);
	eg->storeObjectInArray(1, button2);
}

void InstructionState::virtMouseUp(int iButton, int iX, int iY) {
	Button* goBackButton = dynamic_cast<Button*> (eg->getDisplayableObject(1));

	if (goBackButton && goBackButton->isInClickArea()) {
		eg->setState(std::make_shared<StartUpState>(eg));
		return;
	}
}

InstructionState::~InstructionState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}