#include "Player.h"
#include "Macro.h"

GET_SET(State::Player,std::string,Name)
GET_SET(State::Player,char,ID)

State::Player::Player()
{
    Name("TEST_PLAYER");
    ID(0);
}

State::Player::Player(std::string name,char id)
{
    Name(name);
    ID(id);
}


void State::Player::Relay()
{
    
}
