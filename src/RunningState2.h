#pragma once
#include "State.h"

class RunningState2 :
    public State, public std::enable_shared_from_this<RunningState2>
{
public:
    RunningState2(Scyjz14Engine* engine, bool load = false)
        : State(engine)
        , loadSavedState(load) {}

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

    int getLevelIdentifier() override {
        return 2;
    }

protected:
    int m_backgroundOffsetX = 0;
    int m_backgroundOffsetY = 0;

private:
    bool loadSavedState;
};

