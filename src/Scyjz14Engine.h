#pragma once
#include "BaseEngine.h"
#include "Scyjz14TileManager.h"
#include "State.h"
#include "Scyjz14ImageManager.h"
#include "StartUpState.h"
#include "ExampleFilterPointClasses.h"
#include "LoseState.h"
#include "WinState.h"

class Scyjz14Engine :
    public BaseEngine
{
public:
    Scyjz14Engine(): 
    m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling) 
    {
        m_oTiles.reset(new Scyjz14TileManager);
        //m_pState.reset(new LoseState(this));
        m_pState.reset(new StartUpState(this));
    }
    
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

    void setState(std::shared_ptr<State> newState);
    void restoreState(std::shared_ptr<State> oldState);

    void increaseScore(int num) { score += num; }
    void clearScore() { score = 0; }
    int getScore() { return score; }
    void setBackgroundSurface(DrawingSurface* surface) { m_pBackgroundSurface = surface; }
    void resetBackgroundSurface(){ m_pBackgroundSurface = &m_oTheBackgroundSurface;}

    // Get a reference to the current tile manager - which is defined below!
    Scyjz14TileManager* GetTileManager() { return m_oTiles.get(); }
    FilterPointsScaling* getFilterPointScaling() { return &m_filterScaling; }
    FilterPointsTranslation* getFilterPointsTranslation() { return &m_filterTranslation; }

protected:
    FilterPointsScaling m_filterScaling;
    FilterPointsTranslation m_filterTranslation;

private:
    // Contained object (composition) for the tile manager
    std::unique_ptr<Scyjz14TileManager> m_oTiles;
    std::shared_ptr<State> m_pState;
    int score = 0;
};

