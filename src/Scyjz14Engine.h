#pragma once
#include "BaseEngine.h"
#include "Scyjz14TileManager.h"
#include "State.h"
#include "Scyjz14ImageManager.h"
#include "StartUpState.h"
#include "ExampleFilterPointClasses.h"

class Scyjz14Engine :
    public BaseEngine
{

public:
    Scyjz14Engine(): 
    m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling) 
    {
        m_oTiles.reset(new Scyjz14TileManager);
        state.reset(new StartUpState(this));
    }
    
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsUnderneath() override;
    void virtDrawStringsOnTop() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;
    int virtInitialiseObjects() override;
    int virtInitialise() override;
    void virtMouseWheel(int x, int y, int which, int timestamp) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMainLoopDoBeforeUpdate() override;
    void virtMainLoopPreUpdate() override;
    void copyAllBackgroundBuffer() override;

    // Get a reference to the current tile manager - which is defined below!
    Scyjz14TileManager* GetTileManager() { return m_oTiles.get(); }

    void setState(std::shared_ptr<State> newState) {
        state = newState;

        state->initialise();
        state->initialiseStateObject();
    }

    void restoreState(std::shared_ptr<State> oldState) {
        state = oldState;  // Assuming state is also a std::shared_ptr<State>
    }

    void increaseScore(int num) { score += num; }
    void clearScore() { score = 0; }
    int getScore() { return score; }

    FilterPointsScaling* getFilterPointScaling() { return &m_filterScaling; }
    FilterPointsTranslation* getFilterPointsTranslation() { return &m_filterTranslation; }

protected:
    FilterPointsScaling m_filterScaling;
    FilterPointsTranslation m_filterTranslation;

private:
    // Contained object (composition) for the tile manager
    std::unique_ptr<Scyjz14TileManager> m_oTiles;
    std::shared_ptr<State> state;
    int score = 0;
};

