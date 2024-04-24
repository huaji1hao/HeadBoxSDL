#include "header.h"
#include "PauseState.h"
#include "Button.h"

void PauseState::virtKeyDown(int iKeyCode){
    switch (iKeyCode)
    {
    case SDLK_SPACE: // SPACE Pauses
        eg->unpause();
        eg->restoreState(returnState);
        break;
    }
}

void PauseState::virtDrawStringsOnTop()
{
    eg->drawForegroundString(200, 160, "PAUSE MENU", 0x000000, eg->getFont("resources/Arial_Rounded_Bold.ttf", 48));
}

void PauseState::initialiseStateObject() {
    eg->notifyObjectsAboutMouse(true);
    eg->drawableObjectsChanged();

    Scyjz14ImageObject* board = new Scyjz14ImageObject(100, 50, eg, "resources/game/board.png");

    Button* goBackButton = new Button(280, 315, eg, "resources/UI/GO_BACK_GREY.png");
    //goBackButton->useTopCentreFor00();
    goBackButton->setEnterImage("resources/UI/GO_BACK_BLACK.png");

    Button* resumeButton = new Button(245, 245, eg, "resources/UI/RESUME_GAME_GREY.png");
    resumeButton->setEnterImage("resources/UI/RESUME_GAME_BLACK.png");

    Button* saveButton = new Button(255, 385, eg, "resources/UI/SAVE_GAME_GREY.png");
    saveButton->setEnterImage("resources/UI/SAVE_GAME_BLACK.png");

    eg->appendObjectToArray(board);
    eg->appendObjectToArray(goBackButton);
    eg->appendObjectToArray(resumeButton);
    eg->appendObjectToArray(saveButton);
}

void PauseState::virtMouseUp(int iButton, int iX, int iY) {
    Button* goBackButton = dynamic_cast<Button*> (eg->getDisplayableObject(eg->getContentCount() - 3));
    Button* resumeButton = dynamic_cast<Button*> (eg->getDisplayableObject(eg->getContentCount() - 2));
    Button* saveButton = dynamic_cast<Button*> (eg->getDisplayableObject(eg->getContentCount() - 1));

    if (goBackButton && goBackButton->isInClickArea()) {
        eg->setState(std::make_shared<StartUpState>(eg));
        return;
    }

    if (resumeButton && resumeButton->isInClickArea()) {
        eg->unpause();
        eg->restoreState(returnState);
        return;
    }

    if (saveButton && saveButton->isInClickArea()) {
        
        return;
    }
}

PauseState::~PauseState() {

    for (int i = 1; i <= 4; ++i) {
        DisplayableObject* deleteObj = eg->getDisplayableObject(eg->getContentCount() - 1);
        eg->removeDisplayableObject(deleteObj);
        delete deleteObj;
    }
    
}
