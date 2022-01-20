#include "Player.h"
#include "Actor.h"
#include "WorldHandler.h"
#include "../engine.h"
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
    if(_Behaviour)
    {
        _Behaviour->INT("PlayerID",(int)ID());
        _Behaviour->STRING("PlayerName",Name());
    }

}

void state::Player::AttachPawn(state::Actor* pawn)
{
    pawn->ID(pawn->ID() + (ID() << 8));
    pawn->Property("OWNER",ID());
    _Pawns.push_back(pawn);
}

void state::Player::OnKey(unsigned char* snapshot)
{

    KEY_SCRIPT(snapshot,A)
    KEY_SCRIPT(snapshot,M)
    KEY_SCRIPT(snapshot,I)
    KEY_SCRIPT(snapshot,R)
    KEY_SCRIPT(snapshot,T)

    if(snapshot[sf::Keyboard::O])
        for(state::Manageable* m : state::Manager::GetMgrByName("ACTOR_MGR")->Elements())
            PRINTLN(m->Name() << "::" << std::hex << m->ID());

}

int state::Player::EndTurn(int* params)
{
    char str[32];
    sprintf(str,"EndTurn:%X",params[0] << 8);
    std::cout << str << std::endl;
    state::WorldHandler::NetCommand(std::string(str));
    return 0;
}