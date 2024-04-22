#include "header.h"
#include "RunningState2.h"
#include "Scyjz14Image.h"
#include "BaseEngine.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include "ImagePixelMapping.h"
#include "PauseState.h"
#include "Scyjz14Engine.h"
#include "Weapon.h"
#include "Door.h"
#include <chrono>
#include <thread>

void RunningState2::virtKeyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_SPACE: // SPACE Pauses
		std::shared_ptr<RunningState2> currentState = shared_from_this();
		eg->setState(std::make_shared<PauseState>(eg, currentState));
	}
}

void RunningState2::initialiseStateObject() {

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

	auto nextState = std::make_shared<WinState>(eg);
	eg->storeObjectInArray(10, new Door(400, 300, eg, nextState));

	//refresh zombies randomly on "0" position

	int zombieNumber = 5;
	int secondToMilli = 1000;
	for (int i = 1; i <= zombieNumber; i++) {
		//eg->appendObjectToArray(new Zombie(eg->getWindowWidth(), eg->getWindowHeight(), eg, eg->GetTileManager(), i * secondToMilli));
		//ObjectIndexes::addZombieIndex(eg->getContentCount() - 1);
		eg->storeObjectInArray(i, new Zombie(eg->getWindowWidth(), eg->getWindowHeight(), eg, eg->GetTileManager(), eg->getModifiedTime() + i * secondToMilli));
		ObjectIndexes::addZombieIndex(i);
	}


};

void RunningState2::virtSetupBackgroundBuffer() {
	eg->fillBackground(0xEBDCC7);

	// Draw the background
	Scyjz14Image stains = ImageManager::loadImage("resources/background/uzi.png", true);
	stains.setTransparencyColour(0);
	// Rotate the images and draw them
	DrawingSurface* surface = eg->getBackgroundSurface();
	/*stains.renderImage(surface, 0, 0, 150, 500, 401, 352);
	stains.renderImageApplyingMappingAndTransparency(eg, surface, 150, -120, 401, 401, &ImagePixelMappingRotate(-0.22 * M_PI));
	stains.renderImageApplyingMappingAndTransparency(eg, surface, -255, 110, 401, 401, &ImagePixelMappingRotate(-0.55 * M_PI));
	stains.renderImageApplyingMappingAndTransparency(eg, surface, 470, 110, 410, 401, &ImagePixelMappingRotate(-0.7 * M_PI));*/
	// Draw the tiles
	eg->GetTileManager()->setUpTileManager(eg, "resources/Map/Level2.txt");
	// Draw an rectangle on the screen
	int width = eg->getWindowWidth();
	int height = eg->getWindowHeight();
	eg->drawBackgroundRectangle(width / 2 - 50, height / 2 - 50, width / 2 + 50, height / 2 + 50, 0xffffffff);

}

void RunningState2::virtDrawStringsUnderneath() {
	//// Build the string to print
	//char buf[128];
	//sprintf(buf, "Use 'UP, DOWN, LEFT, RIGHT' and 'W, A, S, D' to control the object");
	//// Print the string
	//eg->drawBackgroundString(50, 10, buf, 0xff00ff, eg->getFont("resources/Truculenta-Regular.ttf", 24));
}

void RunningState2::virtDrawStringsOnTop() {
	char buf[56];
	sprintf(buf, "Score : %d", eg->getScore());
	eg->drawForegroundString(0, 0, buf, 0xff0000, eg->getFont("resources/Truculenta-Regular.ttf", 36));
}

void RunningState2::virtMouseDown(int iButton, int iX, int iY) {
	//eg->setState(new StartUpState(eg));
}

void RunningState2::virtMouseUp(int iButton, int iX, int iY) {
	eg->setState(std::make_shared<StartUpState>(eg));

}

RunningState2::~RunningState2() {

	ObjectIndexes::initialize();
	eg->destroyOldObjects(true);
	eg->clearContents();
}

void RunningState2::virtMainLoopPreUpdate() {

}

void RunningState2::virtMainLoopDoBeforeUpdate() {
	// 获取玩家当前位置
	auto playerid = ObjectIndexes::getPlayerIndexes()[0];
	Player* player = dynamic_cast<Player*>(eg->getDisplayableObject(playerid));

	int playerX = player->getX();
	int playerY = player->getY();

	// 计算背景偏移量
	int offsetX = eg->getWindowWidth() / 2 - playerX;
	int offsetY = eg->getWindowHeight() / 2 - playerY;

	Scyjz14TileManager* tm = eg->GetTileManager();

	// 确保背景偏移量不超出地图边界
	offsetX = std::max(0, std::min(offsetX, tm->getMapWidth() * tm->getTileWidth() - eg->getWindowWidth()));
	offsetY = std::max(0, std::min(offsetY, tm->getMapHeight() * tm->getTileHeight() - eg->getWindowHeight()));

	// 更新背景偏移量
	m_backgroundOffsetX = offsetX;
	m_backgroundOffsetY = offsetY;

	// 根据背景偏移量绘制背景
	tm->drawAllTiles(eg, eg->getBackgroundSurface(), m_backgroundOffsetX, m_backgroundOffsetY);
	dynamic_cast<Door*>(eg->getDisplayableObject(10))->virtDraw(offsetX, offsetY);
}

void RunningState2::copyAllBackgroundBuffer() {
	eg->BaseEngine::copyAllBackgroundBuffer();
	/*eg->getBackgroundSurface()->copyRectangleFrom(eg->getBackgroundSurface(),
		m_backgroundOffsetX, m_backgroundOffsetY,
		eg->getWindowWidth(), eg->getWindowHeight(),
		0, 0);*/
}
