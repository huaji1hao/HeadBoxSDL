#pragma once
#include "BaseEngine.h"
#include "State.h"

class RunningState :
    public State, public std::enable_shared_from_this<RunningState>
{
public:
    // Set the default level to 1
    RunningState(Scyjz14Engine* engine, int level = 1, bool load = false);

    ~RunningState() override;
    
    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsOnTop() override;

    void virtKeyDown(int iKeyCode) override;
    
    void initialiseStateObject() override;

    int getLevelIdentifier() override;

    std::shared_ptr<State> createNextState(Scyjz14Engine* engine, int level);

protected:
    bool isloadSavedState;
    int m_iLevel;
};

