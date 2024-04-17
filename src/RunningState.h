#pragma once
#include "BaseEngine.h"
#include "State.h"

class RunningState :
    public State, public std::enable_shared_from_this<RunningState>
{
public:
    RunningState(Scyjz14Engine* engine) : State(engine)
    {};

    ~RunningState() override;
    
    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

    void initialiseStateObject() override;
    void initialise() override;
    void virtMouseWheel(int x, int y, int which, int timestamp) override;
    void virtKeyDown(int iKeyCode) override;


};

