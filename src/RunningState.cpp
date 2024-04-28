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
		m_pEngine->setState(std::make_shared<PauseState>(m_pEngine, currentState));
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
	m_pEngine->notifyObjectsAboutMouse(false);
	m_pEngine->notifyObjectsAboutKeys(true);
	m_pEngine->drawableObjectsChanged();
	m_pEngine->lockAndSetupBackground();

	m_pEngine->createObjectArray(30);

	m_pEngine->storeObjectInArray(0, new Player(m_pEngine->getWindowWidth() / 2, m_pEngine->getWindowHeight() / 2, m_pEngine, m_pEngine->GetTileManager()));
	ObjectIndexes::addPlayerIndex(0);
	
	m_pEngine->appendObjectToArray(new Sword(0, 0, m_pEngine));

	auto nextState = createNextState(m_pEngine, level);

	m_pEngine->appendObjectToArray(new Door(450, 300, m_pEngine, nextState));

	m_pEngine->appendObjectToArray(new Bullet(0, 0, m_pEngine));

	// Create zombies and set their spawn time one by one
	int zombieNumber = 5 * level;
	int secondToMilli = 1000;
	for (int i = 1; i <= zombieNumber; i++) {
		// Refresh zombies randomly on passable position
		std::pair<int, int> rndPosition = m_pEngine->GetTileManager()->getRandomPassablePoint();
		int zbX = rndPosition.first;
		int zbY = rndPosition.second;
		// Each level has a number of 'level' Boss Zombies
		if(i <= level)
			m_pEngine->storeObjectInArray(i, new Zombie(zbX, zbY, m_pEngine, m_pEngine->GetTileManager(), m_pEngine->getModifiedTime() + i * secondToMilli, true));
		else
			m_pEngine->storeObjectInArray(i, new Zombie(zbX, zbY, m_pEngine, m_pEngine->GetTileManager(), m_pEngine->getModifiedTime() + i * secondToMilli));
		ObjectIndexes::addZombieIndex(i);
	}

	// If the game is loaded from a saved state, load the game state
	if (isloadSavedState) loadGameState("resources/game/game_state/my_state.txt");
};

void RunningState::virtSetupBackgroundBuffer() {
	// Draw the background
	m_pEngine->fillBackground(0xEBDCC7);
	DrawingSurface* surface = m_pEngine->getBackgroundSurface();

	// Define an array of file paths for each level
	const std::array<std::string, 3> mapFiles = {
		"resources/Map/Level1.txt",
		"resources/Map/Level2.txt",
		"resources/Map/Level3.txt"
	};

	// Check if the level index is within the valid range
	if (level >= 1 && level <= mapFiles.size()) {
		std::string mapFile = mapFiles[level - 1]; // Adjust index since 'level' starts at 1
		m_pEngine->GetTileManager()->setUpTileManager(m_pEngine, mapFile.c_str());
	}
	else {
		std::cerr << "Invalid level number: " << level << std::endl;
	}

}

void RunningState::virtDrawStringsOnTop() {
	// Draw the score on the top left corner
	char buf[56];
	sprintf(buf, "Score : %d", m_pEngine->getScore());
	m_pEngine->drawForegroundString(0, 0, buf, 0xff0000, m_pEngine->getFont("resources/Truculenta-Regular.ttf", 36));
}


RunningState::~RunningState() {
	// Clear the game state and destroy the global indexes
	ObjectIndexes::initialize();
	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
}
