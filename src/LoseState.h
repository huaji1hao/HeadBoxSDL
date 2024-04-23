#pragma once
#include "State.h"
class LoseState :
    public State
{
public:
    LoseState(Scyjz14Engine* engine);

    ~LoseState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    // This forces a screen redraw every pass through the loop.
    void virtMainLoopDoBeforeUpdate() override;

private:
    std::vector<DrawingSurface> m_surfaces;
    int m_iCurrentSurfaceNumber = 0;
    const int numSurfaces; // The number of surfaces for animation
    int m_iSwitchThreshold = 10; // Adjust this value to change the switch speed
    int m_iSwitchCounter;
};
