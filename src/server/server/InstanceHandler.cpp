#include "InstanceHandler.h"
#include <sio_client.h>
#include "../shared/engine.h"
#include "../shared/state.h"


void server::InstanceHandler::CreateRoom(std::string room_name)
{
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    Name = room_name;
   io->socket()->emit("req_create_room", room_name+";"+engine::NetMessageHandler::UserName);
}
void server::InstanceHandler::NetCmd(std::string cmd)
{
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    state::WorldHandler::NetCommand(cmd);
    io->socket()->emit("ack_net_cmd",Name+"::"+ cmd);
}
void server::InstanceHandler::CreateUser()
{
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    io->socket()->emit("req_create_user", engine::NetMessageHandler::UserName);
}
void server::InstanceHandler::Start()
{
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    io->socket()->emit("req_start_game", Name);
}