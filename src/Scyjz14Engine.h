#pragma once
#include "BaseEngine.h"
#include "Scyjz14TileManager.h"
#include "State.h"
#include "Scyjz14ImageManager.h"
#include "StartUpState.h"
#include "ExampleFilterPointClasses.h"
#include "Scyjz14FilterPoints.h"

class Scyjz14Engine :
    public BaseEngine
{
public:
    Scyjz14Engine();

    int  virtInitialiseObjects() override;
    int  virtInitialise() override;
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsUnderneath() override;
    void virtDrawStringsOnTop() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;
    void virtMouseWheel(int x, int y, int which, int timestamp) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMainLoopDoBeforeUpdate() override;
    void virtMainLoopPreUpdate() override;
    void copyAllBackgroundBuffer() override;

    // Set a new state for the engine
    void setState(std::shared_ptr<State> newState);
    // Restore a state without initializing it
    void restoreState(std::shared_ptr<State> oldState);
    // Increase the score by num
    void increaseScore(int num);
    // Clear the score
    void clearScore();
    // Get the current score
    int getScore();
    // Set the background surface for the engine
    void setBackgroundSurface(DrawingSurface* surface);
    // Restore the original background surface
    void resetBackgroundSurface();

    // Get a reference to the current tile manager
    Scyjz14TileManager* GetTileManager();
    // Get a reference to the FilterPoints Scaling object
    Scyjz14FilterPoints* getFilterPointScaling();
    // Get a reference to the FilterPoints Translation object
    FilterPointsTranslation* getFilterPointsTranslation();

protected:
    Scyjz14FilterPoints m_filter;

private:
    std::unique_ptr<Scyjz14TileManager> m_oTiles;
    std::shared_ptr<State> m_pState;
    int m_iScore = 0;
};

