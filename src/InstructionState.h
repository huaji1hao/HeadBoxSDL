#pragma once
#include "State.h"
#include "Scyjz14Engine.h"
class InstructionState :
    public State
{
public:
    InstructionState(Scyjz14Engine* engine) : State(engine) {
        
    }
    ~InstructionState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtMainLoopDoBeforeUpdate() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    void virtMouseWheel(int x, int y, int which, int timestamp) override;

    void initialise() override;

    void virtKeyDown(int iKeyCode) override;
};

