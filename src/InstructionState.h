#pragma once
#include "State.h"
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
};

