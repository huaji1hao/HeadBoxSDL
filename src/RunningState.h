#pragma once
#include "BaseEngine.h"
#include "State.h"

class RunningState :
    public State
{
public:
    RunningState(Scyjz14Engine* engine) : State(engine) {};
    ~RunningState();
    
    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

    void initialiseState() override;

};

