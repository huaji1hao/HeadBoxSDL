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
	int oldMouseX = m_pEngine->convertClickedToVirtualPixelXPosition(m_pEngine->getCurrentMouseX());
	int oldMouseY = m_pEngine->convertClickedToVirtualPixelYPosition(m_pEngine->getCurrentMouseY());

	float zoomLevel = m_pEngine->getFilterPointScaling()->getZoomX();
	// Zoom in or out based on the direction of the mouse wheel
	if (y < 0) {
		// cannot be smaller than orgianl size
		if (zoomLevel <= 1) return;
		m_pEngine->getFilterPointScaling()->compress();  // Zoom out
	}
	else if (y > 0) {
		m_pEngine->getFilterPointScaling()->stretch();   // Zoom in
	}

	// Convert screen coordinates to virtual coordinates after zoom
	int newMouseX = m_pEngine->convertClickedToVirtualPixelXPosition(m_pEngine->getCurrentMouseX());
	int newMouseY = m_pEngine->convertClickedToVirtualPixelYPosition(m_pEngine->getCurrentMouseY());

	// Calculate the necessary translation to keep the mouse pointer steady
	int offsetX = newMouseX - oldMouseX;
	int offsetY = newMouseY - oldMouseY;

	// Apply the translation so that the zooming appears centered around the cursor
	m_pEngine->getFilterPointsTranslation()->changeOffset(offsetX, offsetY);

	// Redraw the display to update the changes
	m_pEngine->redrawDisplay(); // Force total redraw
}

void InstructionState::initialise() {
	// Set the scaling filter to the engine
	m_pEngine->getBackgroundSurface()->setDrawPointsFilter(m_pEngine->getFilterPointsTranslation());
	m_pEngine->getForegroundSurface()->setDrawPointsFilter(m_pEngine->getFilterPointsTranslation());
}

void InstructionState::virtKeyDown(int iKeyCode)
{
	// Handle the key press to scroll the foreground
	// Check if the key is in the map
	auto it = keyOffsets.find(iKeyCode);
	if (it != keyOffsets.end()) {
		// If found, apply the corresponding offset
		m_pEngine->getFilterPointsTranslation()->changeOffset(it->second.first, it->second.second);
	}
	else if (iKeyCode == SDLK_SPACE) {
		// Reset offsets if SPACE key is pressed
		m_pEngine->getFilterPointsTranslation()->setOffset(0, 0);
	}

	// Redraw the display after handling the key
	m_pEngine->redrawDisplay();
}

void InstructionState::virtSetupBackgroundBuffer() {
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	DrawingSurface* surface = m_pEngine->getBackgroundSurface();

	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);
}

void InstructionState::initialiseStateObject() {
	m_pEngine->notifyObjectsAboutMouse(true);
	m_pEngine->notifyObjectsAboutKeys(true);
	m_pEngine->drawableObjectsChanged();

	m_pEngine->lockAndSetupBackground();

	// Create array with default size for one object
	m_pEngine->createObjectArray(5);

	Scyjz14ImageObject* instructionImg = new Scyjz14ImageObject(35, 50, m_pEngine, "resources/game/instruction.png");

	Button* button1 = new Button(90, 12, m_pEngine, "resources/UI/GO_BACK_GREY.png");
	button1->useTopCentreFor00();
	button1->setEnterImage("resources/UI/GO_BACK_BLACK.png");

	Button* button2 = new Button(485, 12, m_pEngine, "resources/UI/PLAY_GAME_GREY.png");
	button2->setEnterImage("resources/UI/PLAY_GAME_BLACK.png");

	m_pEngine->storeObjectInArray(0, instructionImg);
	m_pEngine->storeObjectInArray(1, button1);
	m_pEngine->storeObjectInArray(2, button2);	
}

void InstructionState::virtMouseUp(int iButton, int iX, int iY) {
	Button* goBackButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(1));
	Button* playButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(2));

	if (goBackButton && goBackButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<StartUpState>(m_pEngine));
		return;
	}

	if (playButton && playButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<RunningState>(m_pEngine));
		return;
	}
}

InstructionState::~InstructionState() {
	// Restore the engine to its original position and size
	m_pEngine->getFilterPointsTranslation()->setOffset(0, 0);
	m_pEngine->getFilterPointScaling()->resetScalingSize();

	m_pEngine->getBackgroundSurface()->setDrawPointsFilter(nullptr);
	m_pEngine->getForegroundSurface()->setDrawPointsFilter(nullptr);

	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
	m_pEngine->clearScore();
}