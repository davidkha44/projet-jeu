#include "Player.h"
#include "Actor.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Player,std::string,Name)
GET_SET(state::Player,char,ID)

state::Player::Player()
{
    Name("TEST_PLAYER");
    ID(0);
}

state::Player::Player(std::string name,char id)
{
    Name(name);
    ID(id);
}

void state::Player::AttachPawn(state::Actor* pawn)
{
    pawn->ID(pawn->ID() + (ID() << 16));
    pawn->Property("OWNER",ID());
    _Pawns.push_back(pawn);
}



