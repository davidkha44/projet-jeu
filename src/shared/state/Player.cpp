#include "Player.h"
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



