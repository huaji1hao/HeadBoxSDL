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
    virtual void initialiseState() = 0;
    virtual void virtSetupBackgroundBuffer() = 0;
    virtual void virtDrawStringsUnderneath() = 0;
    virtual void virtDrawStringsOnTop() = 0;
    virtual void virtMouseDown(int iButton, int iX, int iY) = 0;

    virtual ~State() {}

protected:
    Scyjz14Engine* eg;
};

