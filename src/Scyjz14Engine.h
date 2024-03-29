#pragma once
#include "BaseEngine.h"
#include "Scyjz14TileManager.h"
#include "State.h"
#include "Scyjz14ImageManager.h"
#include "RunningState.h"
#include "StartUpState.h"

class Scyjz14Engine :
    public BaseEngine
{

public:
    Scyjz14Engine() {
        //setState(new RunningState);
        m_oTiles.reset(new Scyjz14TileManager);
        state.reset(new StartUpState(this));
    }
    
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsUnderneath() override;
    void virtDrawStringsOnTop() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;
    int virtInitialiseObjects() override;

    // Get a reference to the current tile manager - which is defined below!
    Scyjz14TileManager* GetTileManager() { return m_oTiles.get(); }

    void setState(State* newState) {
        state.reset(newState);
        state->initialiseState();
    }



private:
    // Contained object (composition) for the tile manager
    std::unique_ptr<Scyjz14TileManager> m_oTiles;
    std::unique_ptr<State> state;
};

