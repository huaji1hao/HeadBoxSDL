#include "header.h"
#include "Scyjz14Engine.h"
#include "ImagePixelMapping.h"
#include "Scyjz14Image.h"
#include "Player.h"
#include "Button.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include <ctime>

Scyjz14Engine::Scyjz14Engine() : m_filter(0, 0, this)
{
	m_oTiles.reset(new Scyjz14TileManager);
	m_pState.reset(new StartUpState(this));
}

void Scyjz14Engine::setState(std::shared_ptr<State> newState) {
	m_pState = newState;

	m_pState->initialise();
	m_pState->initialiseStateObject();
}

void Scyjz14Engine::restoreState(std::shared_ptr<State> oldState) {
	m_pState = oldState;
}

void Scyjz14Engine::virtSetupBackgroundBuffer()
{
	m_pState->virtSetupBackgroundBuffer();

}

void Scyjz14Engine::virtDrawStringsUnderneath()
{
	m_pState->virtDrawStringsUnderneath();	
}

void Scyjz14Engine::virtDrawStringsOnTop()
{
	m_pState->virtDrawStringsOnTop();
}

void Scyjz14Engine::virtMouseDown(int iButton, int iX, int iY) {
	m_pState->virtMouseDown(iButton, iX, iY);
}

void Scyjz14Engine::virtMouseUp(int iButton, int iX, int iY) {
	m_pState->virtMouseUp(iButton, iX, iY);
}

int Scyjz14Engine::virtInitialiseObjects() {
	// Initialize the object settings
	m_pState->initialiseStateObject();
	return 0;
}

int Scyjz14Engine::virtInitialise() {
	m_pState->initialise();
	return BaseEngine::virtInitialise();
}

void Scyjz14Engine::virtMouseWheel(int x, int y, int which, int timestamp) {
	m_pState->virtMouseWheel(x, y, which, timestamp);
}

void Scyjz14Engine::virtKeyDown(int iKeyCode) {
	m_pState->virtKeyDown(iKeyCode);
}

void Scyjz14Engine::virtMainLoopDoBeforeUpdate() {
	m_pState->virtMainLoopDoBeforeUpdate();
}

void Scyjz14Engine::virtMainLoopPostUpdate(){
	m_pState->virtMainLoopPostUpdate();
}

void Scyjz14Engine::copyAllBackgroundBuffer() {
	m_pState->copyAllBackgroundBuffer();
}

void Scyjz14Engine::increaseScore(int num) { 
	m_iScore += num; 
}

void Scyjz14Engine::clearScore() { 
	m_iScore = 0; 
}

int Scyjz14Engine::getScore() { 
	return m_iScore; 
}

void Scyjz14Engine::setBackgroundSurface(DrawingSurface* surface) { 
	m_pBackgroundSurface = surface; 
}

void Scyjz14Engine::resetBackgroundSurface() { 
	m_pBackgroundSurface = &m_oTheBackgroundSurface; 
}

Scyjz14TileManager* Scyjz14Engine::GetTileManager() { 
	return m_oTiles.get(); 
}

Scyjz14FilterPoints* Scyjz14Engine::getFilterPointScaling() { 
	return &m_filter; 
}

FilterPointsTranslation* Scyjz14Engine::getFilterPointsTranslation() { 
	return m_filter.getFilterPointsTranslation(); 
}



