#pragma once
#include "State.h"
class WinState :
    public State
{
public:
    WinState(Scyjz14Engine* engine) : State(engine) {
    }
    ~WinState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

protected:
    void saveScore(const std::string& name, int score);
};

