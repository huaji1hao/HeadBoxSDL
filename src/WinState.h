#pragma once
#include "State.h"
class WinState :
    public State
{
public:
    WinState(Scyjz14Engine* engine);

    ~WinState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtMainLoopDoBeforeUpdate() override;

    void copyAllBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

protected:
    void saveScore(const std::string& name, int score);
    int m_iOffset; // Offset for the scrolling background
    DrawingSurface leftSurface; // Left surface for the scrolling background
    DrawingSurface rightSurface; // Right surface for the scrolling background

};