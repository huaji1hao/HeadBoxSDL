#include "header.h"
#include "State.h"
#include "Scyjz14Engine.h"

State::~State() {
    eg->clearContents();
}