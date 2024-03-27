#include "header.h"
#include "Zombie.h"
#include "Scyjz14Engine.h"
#include "StartUpState.h"
#include "ObjectIndexes.h"

void StartUpState::virtSetupBackgroundBuffer(){
	eg->fillBackground(0x548746);
}

void StartUpState::virtDrawStringsUnderneath(){

}

void StartUpState::virtDrawStringsOnTop(){

}

void StartUpState::virtMouseDown(int iButton, int iX, int iY) {
	
	eg->setState(new RunningState(eg));

	
}