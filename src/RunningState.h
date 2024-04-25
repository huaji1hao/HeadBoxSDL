#pragma once
#include "BaseEngine.h"
#include "State.h"

class RunningState :
    public State, public std::enable_shared_from_this<RunningState>
{
public:

    RunningState(Scyjz14Engine* engine, int lev = 1, bool load = false) 
    : State(engine)
    , level(lev)
    , isloadSavedState(load)  
    {
        if (level <= 0) level = 1;
    }

    ~RunningState() override;
    
    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtDrawStringsOnTop() override;

    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

    void initialiseStateObject() override;
    void virtKeyDown(int iKeyCode) override;

    int getLevelIdentifier() override{
        return level;
    }

    std::shared_ptr<State> createNextState(Scyjz14Engine* engine, int level);

protected:
    bool isloadSavedState;
    int level;
};

