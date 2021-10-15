#ifndef PLAYER_H
#define PLAYER_H
#include "Macro.hpp"
#include <vector>

class Player
{
    ATTRIBUTE(std::string,Name)
    ATTRIBUTE(std::string,InputSource)
    ATTRIBUTE(int,ID)
    ATTRIBUTE(std::vector<Manageable*>*,Team)
};

#endif