#include "header.h"
#include "PauseState.h"
#include "Button.h"
#include "ObjectIndexes.h"
#include "Player.h"
#include "Zombie.h"

PauseState::PauseState(Scyjz14Engine* engine, std::shared_ptr<State> rtState)
    : State(engine), returnState(rtState){
    if (!m_pEngine->isPaused()) m_pEngine->pause();
};

void PauseState::virtKeyDown(int iKeyCode){
    switch (iKeyCode)
    {
    case SDLK_SPACE: // SPACE Pauses
        m_pEngine->unpause();
        m_pEngine->restoreState(returnState);
        break;
    }
}

void PauseState::virtDrawStringsOnTop()
{
    m_pEngine->drawForegroundString(200, 160, "PAUSE MENU", 0x000000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 48));

    Button* saveButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(m_pEngine->getContentCount() - 1));
    if(saveButton->getClickTimes() > 0)
        m_pEngine->drawForegroundString(270, 430, "Save Successfully !",
            0x000000, m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 20));
}

void PauseState::initialiseStateObject() {
    m_pEngine->notifyObjectsAboutMouse(true);
    m_pEngine->drawableObjectsChanged();

    Scyjz14ImageObject* board = new Scyjz14ImageObject(100, 50, m_pEngine, "resources/game/board.png");

    Button* goBackButton = new Button(280, 315, m_pEngine, "resources/UI/GO_BACK_GREY.png");
    goBackButton->setEnterImage("resources/UI/GO_BACK_BLACK.png");

    Button* resumeButton = new Button(245, 245, m_pEngine, "resources/UI/RESUME_GAME_GREY.png");
    resumeButton->setEnterImage("resources/UI/RESUME_GAME_BLACK.png");

    Button* saveButton = new Button(255, 385, m_pEngine, "resources/UI/SAVE_GAME_GREY.png");
    saveButton->setEnterImage("resources/UI/SAVE_GAME_BLACK.png");

    m_pEngine->appendObjectToArray(board);
    m_pEngine->appendObjectToArray(goBackButton);
    m_pEngine->appendObjectToArray(resumeButton);
    m_pEngine->appendObjectToArray(saveButton);
}

void PauseState::virtMouseUp(int iButton, int iX, int iY) {
    Button* goBackButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(m_pEngine->getContentCount() - 3));
    Button* resumeButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(m_pEngine->getContentCount() - 2));
    Button* saveButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(m_pEngine->getContentCount() - 1));

    if (goBackButton && goBackButton->isInClickArea()) {
        m_pEngine->clearScore();
        m_pEngine->unpause();
        m_pEngine->setState(std::make_shared<StartUpState>(m_pEngine));
        return;
    }

    if (resumeButton && resumeButton->isInClickArea()) {
        m_pEngine->unpause();
        m_pEngine->restoreState(returnState);
        return;
    }

    if (saveButton && saveButton->isInClickArea() && saveButton->getClickTimes() <= 0) {
        saveGameState("resources/game/game_state/my_state.txt", returnState->getLevelIdentifier());
        return;
    }
}

PauseState::~PauseState() {
    m_pEngine->notifyObjectsAboutMouse(false);

    // Manually delete the objects otherwise they will be shown in the next state
    for (int i = 1; i <= 4; ++i) {
        DisplayableObject* deleteObj = m_pEngine->getDisplayableObject(m_pEngine->getContentCount() - 1);
        m_pEngine->removeDisplayableObject(deleteObj);
        delete deleteObj;
    }
}