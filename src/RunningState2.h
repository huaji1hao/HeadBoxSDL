#pragma once
#include "State.h"

class RunningState2 :
    public State, public std::enable_shared_from_this<RunningState2>
{
public:
    RunningState2(Scyjz14Engine* engine) : State(engine)
    {};

    ~RunningState2() override;

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

