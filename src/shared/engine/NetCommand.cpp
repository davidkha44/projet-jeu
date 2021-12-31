#include "../../client/client/Macro.hpp"
#include "NetCommand.h"
#define COMMA ,


GET_SET(engine::NetCommand,std::string, Name)
GET_SET(engine::NetCommand,std::pair<std::string COMMA std::string>,Format)


engine::NetCommand::NetCommand(std::vector<std::string> args)
{
    Name(args[0]);
    _Format.first = args[1];
    _Format.second = args[2];
    NetCommands[args[0]] = this;
}

engine::NetCommand::NetCommand(std::string args) 
{

}