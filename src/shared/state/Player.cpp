#include "Player.h"
#include "Actor.h"
#include "WorldHandler.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Player,std::string,Name)
GET_SET(state::Player,char,ID)
GET_SET(state::Player,engine::Script*,Behaviour)

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
state::Player::Player(std::string name,char id,engine::Script* behaviour)
{
    Name(name);
    ID(id);
    _Behaviour = behaviour;
}

void state::Player::AttachPawn(state::Actor* pawn)
{
    pawn->ID(pawn->ID() + (ID() << 16));
    pawn->Property("OWNER",ID());
    _Pawns.push_back(pawn);
}

void state::Player::OnKey(unsigned char* snapshot)
{
    
    KEY_SCRIPT(snapshot,A)
    KEY_SCRIPT(snapshot,M)
    KEY_SCRIPT(snapshot,I)
    KEY_SCRIPT(snapshot,R)
        
}

