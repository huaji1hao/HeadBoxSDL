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
    void virtKeyDown(int iKeyCode) override;

    void virtMainLoopPreUpdate() override;

    void virtMainLoopDoBeforeUpdate() override;

    void copyAllBackgroundBuffer() override;

protected:
    int m_backgroundOffsetX = 0;
    int m_backgroundOffsetY = 0;

};

