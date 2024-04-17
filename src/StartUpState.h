#pragma once
#include "State.h"
#include "BaseEngine.h"
class StartUpState :
    public State
{
public:
    StartUpState(Scyjz14Engine* engine) : State(engine) {
    }
    ~StartUpState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;
};

