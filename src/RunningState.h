#pragma once
#include "BaseEngine.h"
#include "State.h"

class RunningState :
    public State
{
public:
    RunningState(Scyjz14Engine* engine) : State(engine) {};
    
    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY){}

    void initialiseState() override;

};

