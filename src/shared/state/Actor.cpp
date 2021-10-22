#include "Actor.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Actor,int,HP)
GET_SET(state::Actor,int,AP)
GET_SET(state::Actor,int,MP)
GET_SET(state::Actor,int,DMG)
GET_SET(state::Actor,int,DEF)

state::Actor::Actor() : state::Manageable()
{
    HP(0);
    MP(0);
    AP(0);
    DMG(0);
    DEF(0);
}