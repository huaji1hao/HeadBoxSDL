#include "header.h"
#include "Scyjz14Engine.h"
#include "ImagePixelMapping.h"
#include "Scyjz14Image.h"
#include "Player.h"
#include "Button.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include <ctime>

void Scyjz14Engine::setState(std::shared_ptr<State> newState) {
	m_pState = newState;

	m_pState->initialise();
	m_pState->initialiseStateObject();
}

void Scyjz14Engine::restoreState(std::shared_ptr<State> oldState) {
	m_pState = oldState;  // Assuming m_pState is also a std::shared_ptr<State>
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

void Scyjz14Engine::virtMainLoopPreUpdate() {
	m_pState->virtMainLoopPreUpdate();
}

void Scyjz14Engine::copyAllBackgroundBuffer() {
	m_pState->copyAllBackgroundBuffer();
}



