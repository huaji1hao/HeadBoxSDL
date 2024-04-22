#pragma once
#include "State.h"
class LoseState :
    public State
{
public:
    LoseState(Scyjz14Engine* engine) : State(engine) {
    }
    ~LoseState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseUp(int iButton, int iX, int iY) override;
};

