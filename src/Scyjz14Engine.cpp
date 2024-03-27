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

int Scyjz14Engine::virtInitialiseObjects() {
	// Initialize the object settings
	notifyObjectsAboutMouse(true);
	drawableObjectsChanged();
	destroyOldObjects(true);

	// Add objects to the engine
	appendObjectToArray(new Button(400, 400, this, "resources/cyan-button.png"));
	ObjectIndexes::addStartUpIndex(getContentCount() - 1);

	appendObjectToArray(new Player(this, &m_oTiles));
	// Add indexes to the global, make sure do this after add it into array
	ObjectIndexes::addPlayerIndexes({getContentCount() - 1});

	// Make only start up UI visible to start with
	setOnlyStartUpObjectsVisible();
	return 0;
}

void Scyjz14Engine::setOnlyStartUpObjectsVisible() {
	setAllObjectsVisible(false);
	for (auto& id : ObjectIndexes::getStartUpIndexes())
		getDisplayableObject(id)->setVisible(true);
}




