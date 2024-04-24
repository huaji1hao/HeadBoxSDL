#pragma once
#include "Scyjz14Engine.h"
#include "State.h"

class PauseState :
    public State
{
public:
    PauseState(Scyjz14Engine* engine, std::shared_ptr<State> rtState) : State(engine),
    returnState(rtState) {
        if (!eg->isPaused()) eg->pause();
    };

    ~PauseState();

    void virtKeyDown(int iKeyCode) override;

    void initialiseStateObject() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    void virtDrawStringsOnTop() override;

protected:
    std::shared_ptr<State> returnState;
};

