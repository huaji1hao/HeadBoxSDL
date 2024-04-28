#pragma once
#include "Scyjz14Engine.h"
#include "State.h"

class PauseState :
    public State
{
public:
    // Set the target state to return when initialized
    PauseState(Scyjz14Engine* engine, std::shared_ptr<State> rtState);

    ~PauseState();

    void virtKeyDown(int iKeyCode) override;

    void initialiseStateObject() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    void virtDrawStringsOnTop() override;

protected:
    std::shared_ptr<State> returnState;
};

