#pragma once
#include "header.h"
#include "BaseEngine.h"

class Scyjz14Engine;

// State interface
class State
{
public:
    State(Scyjz14Engine * engine): m_pEngine(engine) {}
    virtual void initialise() {};
    virtual void initialiseStateObject() {};
    virtual void virtSetupBackgroundBuffer() {};
    virtual void virtDrawStringsUnderneath() {};
    virtual void virtDrawStringsOnTop() {};
    virtual void virtMouseDown(int iButton, int iX, int iY) {};
    virtual void virtMouseUp(int iButton, int iX, int iY) {};
    virtual void virtMouseWheel(int x, int y, int which, int timestamp) {};
    virtual void virtKeyDown(int iKeyCode) {};
    virtual void virtMainLoopDoBeforeUpdate() {};
    virtual void virtMainLoopPreUpdate() {};
    virtual void copyAllBackgroundBuffer();
    virtual int getLevelIdentifier();
    virtual ~State() {};

    // load the game state from a file
    void loadGameState(const std::string& filename);
    // save the game state to a file with the level identifier
    void saveGameState(const std::string& filename, int LevelIdentifier);
    // determine the level identifier from the save file
    int determineLevelFromSaveFile(const std::string& filename);

protected:
    Scyjz14Engine* m_pEngine;
};

