#include "header.h"
#include "RunningState.h"
#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include "ImagePixelMapping.h"
#include "PauseState.h"
#include "Scyjz14Engine.h"
#include "Weapon.h"
#include "Door.h"
#include "RunningState2.h"

void RunningState::virtKeyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_SPACE: // SPACE Pauses
		std::shared_ptr<RunningState> currentState = shared_from_this();
		eg->setState(std::make_shared<PauseState>(eg, currentState));
	}
}

void RunningState::initialiseStateObject() {
	
	eg->notifyObjectsAboutMouse(true);
	eg->drawableObjectsChanged();
	eg->lockAndSetupBackground();
	//eg->redrawDisplay();

	eg->createObjectArray(20);

	eg->storeObjectInArray(0, new Player(eg->getWindowWidth() / 2, eg->getWindowHeight() / 2, eg, eg->GetTileManager()));
	ObjectIndexes::addPlayerIndex(0);
	//eg->appendObjectToArray(new Player(eg->getWindowWidth() / 2, eg->getWindowHeight() / 2, eg, eg->GetTileManager()));
	//ObjectIndexes::addPlayerIndex( eg->getContentCount() - 1 );
	
	eg->appendObjectToArray(new Weapon(0, 0, eg));

	auto nextState = std::make_shared<RunningState2>(eg);
	eg->storeObjectInArray(10, new Door(400, 300, eg, nextState));

	//refresh zombies randomly on "0" position

	int zombieNumber = 5;
	int secondToMilli = 1000;
	for (int i = 1; i <= zombieNumber; i++) {
		std::pair<int, int> rndPosition = eg->GetTileManager()->getRandomPassablePoint();
		int zbX = rndPosition.first;
		int zbY = rndPosition.second;

		eg->storeObjectInArray(i, new Zombie(zbX, zbY, eg, eg->GetTileManager(), eg->getModifiedTime() + i * secondToMilli));
		ObjectIndexes::addZombieIndex(i);
	}

	
};

void RunningState::virtSetupBackgroundBuffer() {
	eg->fillBackground(0xEBDCC7);

	// Draw the background
	Scyjz14Image stains = ImageManager::loadImage("resources/background/uzi.png", true);
	stains.setTransparencyColour(0);
	// Rotate the images and draw them
	DrawingSurface* surface = eg->getBackgroundSurface();
	// Draw the tiles
	eg->GetTileManager()->setUpTileManager(eg, "resources/Map/Level1.txt");
	// Draw an rectangle on the screen
	int width = eg->getWindowWidth();
	int height = eg->getWindowHeight();
	eg->drawBackgroundRectangle(width / 2 - 50, height / 2 - 50, width / 2 + 50, height / 2 + 50, 0xffffffff);

}

void RunningState::virtDrawStringsUnderneath() {
	//// Build the string to print
	//char buf[128];
	//sprintf(buf, "Use 'UP, DOWN, LEFT, RIGHT' and 'W, A, S, D' to control the object");
	//// Print the string
	//eg->drawBackgroundString(50, 10, buf, 0xff00ff, eg->getFont("resources/Truculenta-Regular.ttf", 24));
}

void RunningState::virtDrawStringsOnTop() {
	char buf[56];
	sprintf(buf, "Score : %d", eg->getScore());
	eg->drawForegroundString(0, 0, buf, 0xff0000, eg->getFont("resources/Truculenta-Regular.ttf", 36));
}

void RunningState::virtMouseDown(int iButton, int iX, int iY) {
	
}

void RunningState::virtMouseUp(int iButton, int iX, int iY) {
	/*eg->setState(std::make_shared<StartUpState>(eg));*/
}

RunningState::~RunningState() {
	ObjectIndexes::initialize();
	eg->destroyOldObjects(true);
	eg->clearContents();
}
