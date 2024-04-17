#include "header.h"
#include "Scyjz14Engine.h"
#include "ImagePixelMapping.h"
#include "Scyjz14Image.h"
#include "Player.h"
#include "Button.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include <ctime>

void Scyjz14Engine::virtSetupBackgroundBuffer()
{
	state->virtSetupBackgroundBuffer();

}

void Scyjz14Engine::virtDrawStringsUnderneath()
{
	state->virtDrawStringsUnderneath();
	
}

void Scyjz14Engine::virtDrawStringsOnTop()
{
	state->virtDrawStringsOnTop();
	
}

void Scyjz14Engine::virtMouseDown(int iButton, int iX, int iY) {
	state->virtMouseDown(iButton, iX, iY);
}

void Scyjz14Engine::virtMouseUp(int iButton, int iX, int iY) {
	state->virtMouseUp(iButton, iX, iY);
}

int Scyjz14Engine::virtInitialiseObjects() {

	// Initialize the object settings
	state->initialiseStateObject();

	return 0;
}

int Scyjz14Engine::virtInitialise() {
	state->initialise();
	return BaseEngine::virtInitialise();
}

void Scyjz14Engine::virtMouseWheel(int x, int y, int which, int timestamp) {
	state->virtMouseWheel(x, y, which, timestamp);
}

void Scyjz14Engine::virtKeyDown(int iKeyCode) {
	state->virtKeyDown(iKeyCode);
}



