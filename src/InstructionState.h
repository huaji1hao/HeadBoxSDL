#pragma once
#include "State.h"
#include "Scyjz14Engine.h"
class InstructionState :
    public State
{
public:
    // This state is used to display the instruction of the game
    InstructionState(Scyjz14Engine* engine) : State(engine) {}

    ~InstructionState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    void virtMouseWheel(int x, int y, int which, int timestamp) override;

    void initialise() override;

    void virtKeyDown(int iKeyCode) override;

protected:
    // Define a map that associates keys with x and y offsets
    const std::map<int, std::pair<int, int>> keyOffsets = {
        {SDLK_LEFT, {-10, 0}},
        {SDLK_RIGHT, {10, 0}},
        {SDLK_UP, {0, -10}},
        {SDLK_DOWN, {0, 10}}
    };
};

