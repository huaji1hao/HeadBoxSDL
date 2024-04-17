#include "header.h"
#include "PauseState.h"

void PauseState::virtKeyDown(int iKeyCode){
    switch (iKeyCode)
    {
    case SDLK_SPACE: // SPACE Pauses
        eg->unpause();
        eg->restoreState(returnState);
        break;
    }
}

void PauseState::virtDrawStringsUnderneath()
{
    eg->drawForegroundString(200, 300, "Paused. Press SPACE to continue", 0x000000, NULL);
}
