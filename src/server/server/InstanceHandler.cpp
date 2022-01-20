#include "InstanceHandler.h"
#include <sio_client.h>
#include <fstream>
#include <iostream>
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
    //state::WorldHandler::NetCommand(cmd);
    io->socket()->emit("ack_net_cmd",Name+"::"+ cmd);
}
void server::InstanceHandler::CreateUser()
{
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    io->socket()->emit("req_create_user", engine::NetMessageHandler::UserName);
}
void server::InstanceHandler::Start()
{
    // state::World* w = state::WorldHandler::CurrentWorld;
    // std::ifstream file(w->ResPath());
    // std::cout << "W DIM : " << w->CellN().x <<"::"<< w->CellN().y << std::endl;
    // state::Manager* mgr = state::Manager::GetMgrByID(0);
    // int lines = 0,col = 0;
    // for( std::string line; getline( file, line ); )
    // {
    //     if(line.find('#') == std::string::npos)
    //     {
    //         std::vector<std::string> strs = engine::FileHandler::SplitString(line,",");
    //         for(int i = 0; i < w->CellN().x;i++)
    //         {
    //             state::Manageable* ref = mgr->GetByID(std::stoi(strs[i]));
    //             state::Manageable* item = new state::Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),ref->Name());
    //             item->ID(0xFF000000 + ((std::stoi(strs[i]) & 0xFF) << 16) +((col & 0xFF) << 8) + (lines & 0xFF));
    //             item->AssignPosition(col,lines);
    //             state::Manager::GetMgrByID(1)->Add(item);
    //             col++;
    //         } 
    //     }
    //     col = 0;
    //     lines++;
    //     if(lines == w->CellSize().y)
    //         return;
    // }
    // std::cout << "INIT ACTOR" << std::endl;
    // engine::FileHandler::DeserializeTable<engine::Pattern>("res/tables/Patterns.csv","CSV");
    // engine::FileHandler::DeserializeTable<engine::NetCommand>("res/tables/NetMessage.csv","CSV");
    // engine::FileHandler::DeserializeTable<engine::Action>("res/tables/Actions.csv","CSV");
    // if(state::WorldHandler::CurrentWorld->Behaviour())
    //     state::WorldHandler::CurrentWorld->Behaviour()->Run();
    // if(state::WorldHandler::Behaviour)
    // {
    //     state::WorldHandler::Behaviour->EVENTS["OnTurnBegin"] = state::WorldHandler::OnTurnBegin;
    //     state::WorldHandler::Behaviour->EVENTS["OnTurnEnd"] = state::WorldHandler::OnTurnEnd;
    //     state::WorldHandler::Behaviour->Run();
    //     for(state::Player* p : state::WorldHandler::Players)
    //         if(p->Behaviour())
    //             p->Behaviour()->RunFunction("InitializePlayer",(int*)NULL);
    // }
    sio::client* io = (sio::client*)engine::NetMessageHandler::IO;
    io->socket()->emit("req_start_game", Name);
}