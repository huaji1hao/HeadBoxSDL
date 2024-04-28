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
    std::vector<DrawingSurface> m_surfaces; // The surfaces for animation
    int m_iCurrentSurfaceNumber = 0; // The current surface number
    const int numSurfaces; // The number of surfaces for animation
    int m_iSwitchThreshold; // Higher the threshold, the slower the animation
    int m_iSwitchCounter; // The counter for threshold
};
