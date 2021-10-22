#include "Actor.h"
#include "Macro.h"

GET_SET(State::Actor,int,HP)
GET_SET(State::Actor,int,AP)
GET_SET(State::Actor,int,MP)
GET_SET(State::Actor,int,DMG)
GET_SET(State::Actor,int,DEF)

State::Actor::Actor() : State::Manageable()
{
    HP(0);
    MP(0);
    AP(0);
    DMG(0);
    DEF(0);
}