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

void LoseState::virtSetupBackgroundBuffer() {
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	DrawingSurface* surface = eg->getBackgroundSurface();
	//title.renderImageWithMask(surface, 0, 0, 150, 200, 400, 169, -1);
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);

}

void LoseState::virtDrawStringsUnderneath() {

	// Print the string
	eg->drawBackgroundString(50, 80, "Your died!",
		0xff0000, eg->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	// Build the string to print
	char buf[56];
	sprintf(buf, "Your score is %d", eg->getScore());

	eg->drawBackgroundString(237, 150, buf, 0xff0000, eg->getFont("resources/Arial_Rounded_Bold.ttf", 36));
}

void LoseState::virtDrawStringsOnTop() {

}

void LoseState::initialiseStateObject() {
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(5);
	Button* button1 = new Button(220, 310, eg, "resources/UI/SEND_SCORE_GREY.png");
	button1->setEnterImage("resources/UI/SEND_SCORE_BLACK.png");
	//button1->setJumpState(true);
	Button* button2 = new Button(220, 390, eg, "resources/UI/GO_BACK_GREY.png");
	button2->setEnterImage("resources/UI/GO_BACK_BLACK.png");
	button2->setJumpState(false);

	TextInputField* textField = new TextInputField(220, 240, 270, 40, eg, eg->getFont("resources/Arial_Rounded_Bold.ttf", 27));

	eg->storeObjectInArray(0, button1);
	eg->storeObjectInArray(1, button2);
	eg->storeObjectInArray(2, textField);

}

void LoseState::virtMouseUp(int iButton, int iX, int iY) {
	
}

LoseState::~LoseState() {
	eg->destroyOldObjects(true);
	eg->clearContents();
}