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
#include "ImagePixelMappingFlip.h"

void InstructionState::virtMouseWheel(int x, int y, int which, int timestamp) {
	// Convert screen coordinates to virtual coordinates before zoom
	int oldMouseX = eg->convertClickedToVirtualPixelXPosition(eg->getCurrentMouseX());
	int oldMouseY = eg->convertClickedToVirtualPixelYPosition(eg->getCurrentMouseY());

	float zoomLevel = eg->getFilterPointScaling()->getZoomX();
	// Zoom in or out based on the direction of the mouse wheel
	if (y < 0) {
		// cannot be smaller than orgianl size
		if (zoomLevel <= 1) return;
		eg->getFilterPointScaling()->compress();  // Zoom out
	}
	else if (y > 0) {
		eg->getFilterPointScaling()->stretch();   // Zoom in
	}

	// Convert screen coordinates to virtual coordinates after zoom
	int newMouseX = eg->convertClickedToVirtualPixelXPosition(eg->getCurrentMouseX());
	int newMouseY = eg->convertClickedToVirtualPixelYPosition(eg->getCurrentMouseY());

	// Calculate the necessary translation to keep the mouse pointer steady
	int offsetX = newMouseX - oldMouseX;
	int offsetY = newMouseY - oldMouseY;

	// Apply the translation so that the zooming appears centered around the cursor
	eg->getFilterPointsTranslation()->changeOffset(offsetX, offsetY);

	// Redraw the display to update the changes
	eg->redrawDisplay(); // Force total redraw
}

void InstructionState::initialise() {
	eg->getBackgroundSurface()->setDrawPointsFilter(eg->getFilterPointsTranslation());
	eg->getForegroundSurface()->setDrawPointsFilter(eg->getFilterPointsTranslation());
}

void InstructionState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_LEFT:
		eg->getFilterPointsTranslation()->changeOffset(10, 0);
		eg->redrawDisplay();
		break;
	case SDLK_RIGHT:
		eg->getFilterPointsTranslation()->changeOffset(-10, 0);
		eg->redrawDisplay();
		break;
	case SDLK_UP:
		eg->getFilterPointsTranslation()->changeOffset(0, 10);
		eg->redrawDisplay();
		break;
	case SDLK_DOWN:
		eg->getFilterPointsTranslation()->changeOffset(0, -10);
		eg->redrawDisplay();
		break;
	case SDLK_SPACE: // Space moves the top left back to the zero coordinates - to be on initial location
		eg->getFilterPointsTranslation()->setOffset(0, 0);
		eg->redrawDisplay();
		break;
	}
}


void InstructionState::virtMainLoopDoBeforeUpdate() {
	

}

void InstructionState::virtDrawStringsUnderneath() {

}

void InstructionState::virtDrawStringsOnTop() {

}

void InstructionState::virtSetupBackgroundBuffer() {

	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);
	//Scyjz14Image torch = Scyjz14ImageManager::loadImage("resources/game/explosion/torch.png", true);

	DrawingSurface* surface = eg->getBackgroundSurface();


	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);

	/*torch.renderImageWithAlpha(surface, 0, 0, 100, 100, torch.getWidth(), torch.getHeight());
	ImagePixelMappingFlip flipMapper(ImagePixelMappingFlip::VERTICAL);
	torch.renderImageWithAlphaAndApplyingMapping(eg, surface, 0, 0, 50, 50, torch.getWidth(), torch.getHeight(), &flipMapper);*/
}

void InstructionState::initialiseStateObject() {
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();

	eg->lockAndSetupBackground();

	// Create array with default size for one object
	eg->createObjectArray(5);

	Scyjz14ImageObject* instructionImg = new Scyjz14ImageObject(35, 30, eg, "resources/game/instruction.png");

	Button* button1 = new Button(90, 1, eg, "resources/UI/GO_BACK_GREY.png");
	button1->useTopCentreFor00();
	button1->setEnterImage("resources/UI/GO_BACK_BLACK.png");

	Button* button2 = new Button(365, 378, eg, "resources/UI/PLAY_GAME_GREY.png");
	button2->setEnterImage("resources/UI/PLAY_GAME_BLACK.png");

	eg->storeObjectInArray(0, instructionImg);
	eg->storeObjectInArray(1, button1);
	eg->storeObjectInArray(2, button2);
	
	
}

void InstructionState::virtMouseUp(int iButton, int iX, int iY) {
	Button* goBackButton = dynamic_cast<Button*> (eg->getDisplayableObject(1));
	Button* playButton = dynamic_cast<Button*> (eg->getDisplayableObject(2));

	if (goBackButton && goBackButton->isInClickArea()) {
		eg->setState(std::make_shared<StartUpState>(eg));
		return;
	}

	if (playButton && playButton->isInClickArea()) {
		eg->setState(std::make_shared<RunningState>(eg));
		return;
	}
}

InstructionState::~InstructionState() {
	eg->getFilterPointsTranslation()->setOffset(0, 0);
	eg->getFilterPointScaling()->resetScalingSize();

	eg->getBackgroundSurface()->setDrawPointsFilter(nullptr);
	eg->getForegroundSurface()->setDrawPointsFilter(nullptr);

	eg->destroyOldObjects(true);
	eg->clearContents();
}