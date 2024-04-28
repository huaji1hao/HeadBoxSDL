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
#include <array>
#include <string>


RunningState::RunningState(Scyjz14Engine* engine, int lev, bool load)
	: State(engine)
	, level(lev)
	, isloadSavedState(load)
{
	// Ensure the level is within the valid range
	if (level < 1 || level > 3) level = 1;
}

int RunningState::getLevelIdentifier() {
	return level;
}

void RunningState::virtKeyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // when ESC is pressed, pause the game
		std::shared_ptr<RunningState> currentState = shared_from_this();
		eg->setState(std::make_shared<PauseState>(eg, currentState));
	}
}

std::shared_ptr<State> RunningState::createNextState(Scyjz14Engine* engine, int level) {
	// If the level is 3, return the WinState
	if (level + 1 > 3) {
		return std::make_shared<WinState>(engine);
	}
	// Otherwise, return a new RunningState with the next level
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
	
	eg->appendObjectToArray(new Sword(0, 0, eg));

	auto nextState = createNextState(eg, level);

	eg->appendObjectToArray(new Door(450, 300, eg, nextState));

	eg->appendObjectToArray(new Bullet(0, 0, eg));

	// Create zombies and set their spawn time one by one
	int zombieNumber = 5 * level;
	int secondToMilli = 1000;
	for (int i = 1; i <= zombieNumber; i++) {
		// Refresh zombies randomly on passable position
		std::pair<int, int> rndPosition = eg->GetTileManager()->getRandomPassablePoint();
		int zbX = rndPosition.first;
		int zbY = rndPosition.second;
		// Each level has a number of 'level' Boss Zombies
		if(i <= level)
			eg->storeObjectInArray(i, new Zombie(zbX, zbY, eg, eg->GetTileManager(), eg->getModifiedTime() + i * secondToMilli, true));
		else
			eg->storeObjectInArray(i, new Zombie(zbX, zbY, eg, eg->GetTileManager(), eg->getModifiedTime() + i * secondToMilli));
		ObjectIndexes::addZombieIndex(i);
	}

	// If the game is loaded from a saved state, load the game state
	if (isloadSavedState) loadGameState("resources/game/game_state/my_state.txt");
};

void RunningState::virtSetupBackgroundBuffer() {
	// Draw the background
	eg->fillBackground(0xEBDCC7);
	DrawingSurface* surface = eg->getBackgroundSurface();

	// Define an array of file paths for each level
	const std::array<std::string, 3> mapFiles = {
		"resources/Map/Level1.txt",
		"resources/Map/Level2.txt",
		"resources/Map/Level3.txt"
	};

	// Check if the level index is within the valid range
	if (level >= 1 && level <= mapFiles.size()) {
		std::string mapFile = mapFiles[level - 1]; // Adjust index since 'level' starts at 1
		eg->GetTileManager()->setUpTileManager(eg, mapFile.c_str());
	}
	else {
		std::cerr << "Invalid level number: " << level << std::endl;
	}

}

void RunningState::virtDrawStringsOnTop() {
	// Draw the score on the top left corner
	char buf[56];
	sprintf(buf, "Score : %d", eg->getScore());
	eg->drawForegroundString(0, 0, buf, 0xff0000, eg->getFont("resources/Truculenta-Regular.ttf", 36));
}


RunningState::~RunningState() {
	// Clear the game state and destroy the global indexes
	ObjectIndexes::initialize();
	eg->destroyOldObjects(true);
	eg->clearContents();
}
