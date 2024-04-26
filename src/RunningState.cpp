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
#include "WinState.h"
#include "Bullet.h"

void RunningState::virtKeyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // SPACE Pauses SDLK_SPACE
		std::shared_ptr<RunningState> currentState = shared_from_this();
		eg->setState(std::make_shared<PauseState>(eg, currentState));
	}
}

std::shared_ptr<State> RunningState::createNextState(Scyjz14Engine* engine, int level) {
	// create state according to current level
	if (level + 1 > 3) {
		return std::make_shared<WinState>(engine);
	}
	else {
		return std::make_shared<RunningState>(engine, level + 1);
	}
}


void RunningState::initialiseStateObject() {
	eg->notifyObjectsAboutMouse(false);
	eg->notifyObjectsAboutKeys(true);
	eg->drawableObjectsChanged();
	eg->lockAndSetupBackground();

	eg->createObjectArray(30);

	eg->storeObjectInArray(0, new Player(eg->getWindowWidth() / 2, eg->getWindowHeight() / 2, eg, eg->GetTileManager()));
	ObjectIndexes::addPlayerIndex(0);
	
	eg->appendObjectToArray(new Weapon(0, 0, eg));

	auto nextState = createNextState(eg, level);

	eg->appendObjectToArray(new Door(450, 300, eg, nextState));

	eg->appendObjectToArray(new Bullet(0, 0, eg));

	//refresh zombies randomly on passable position
	int zombieNumber = 5 * level;
	int secondToMilli = 1000;
	for (int i = 1; i <= zombieNumber; i++) {
		std::pair<int, int> rndPosition = eg->GetTileManager()->getRandomPassablePoint();
		int zbX = rndPosition.first;
		int zbY = rndPosition.second;

		eg->storeObjectInArray(i, new Zombie(zbX, zbY, eg, eg->GetTileManager(), eg->getModifiedTime() + i * secondToMilli));
		ObjectIndexes::addZombieIndex(i);
	}

	if (isloadSavedState) loadGameState("resources/game/game_state/my_state.txt");

	
};

void RunningState::virtSetupBackgroundBuffer() {
	eg->fillBackground(0xEBDCC7);

	// Draw the background
	Scyjz14Image stains = ImageManager::loadImage("resources/background/uzi.png", true);
	stains.setTransparencyColour(0);
	// Rotate the images and draw them
	DrawingSurface* surface = eg->getBackgroundSurface();

	// Draw the tiles
	std::string mapFile = "";
	if (level == 1) {
		mapFile = "resources/Map/Level1.txt";
	}
	else if (level == 2) {
		mapFile = "resources/Map/Level2.txt";
	}
	else if (level == 3) {
		mapFile = "resources/Map/Level3.txt";
	}

	eg->GetTileManager()->setUpTileManager(eg, mapFile.c_str());
	// Draw an rectangle on the screen
	//int width = eg->getWindowWidth();
	//int height = eg->getWindowHeight();
	//eg->drawBackgroundRectangle(width / 2 - 50, height / 2 - 50, width / 2 + 50, height / 2 + 50, 0xffffffff);

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
