#include "StateEvent.h"

using namespace state;

StateEvent::StateEvent (StateEventID se): StateEventid(se){};
StateEvent::~StateEvent(){};
void StateEvent::setStateEventID (StateEventID newID){
    StateEventid=newID;
}