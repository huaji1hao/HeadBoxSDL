#pragma once
#include "header.h"
#include "BaseEngine.h"

class Scyjz14Engine;

// State interface
class State
{
public:
    State(Scyjz14Engine * engine): eg(engine) {

    }
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

    
    void loadGameState(const std::string& filename);
    void saveGameState(const std::string& filename, int LevelIdentifier);
    int determineLevelFromSaveFile(const std::string& filename);

protected:
    Scyjz14Engine* eg;
};

