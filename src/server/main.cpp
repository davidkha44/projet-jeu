#include <iostream>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <sio_client.h>
#include <thread>
#include <engine.h>
#include <state.h>
#include <server.h>
#include <SFML/Graphics.hpp>


using namespace sio;
using namespace sf;
using namespace std;
using namespace state;
using namespace engine;
using namespace server;

client io;
int iter = 0;


int main(int argc,char* argv[])
{
    std::vector<std::string> players_name;
    string endpoint(argv[1]);
    io.connect(endpoint + ":3000");
    NetMessageHandler::UserName = "HostServer";
    NetMessageHandler::IO = &io;
    FileHandler::LoadLaunchArgs("res/tables/LaunchArgs.csv");
    FileHandler::DeserializeTable<Manager>("res/tables/Managers.csv","CSV");
    Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("res/tables/ManageablesVisuals.csv","CSV_SERVER_SIDE"));
    WorldHandler::Initialize();
    io.set_open_listener([&]() {

        cout << "CONNECTED "  << endl;
        InstanceHandler::CreateUser();
        InstanceHandler::CreateRoom("BackRoom");
        thread t(NetMessageHandler::KeepAlive);
        t.detach();
        io.socket()->on("req_net_cmd",[&](sio::event& ev)
        {
        cout << "NET_CMD IS : " << ev.get_message()->get_string() << endl;
            InstanceHandler::NetCmd(ev.get_message()->get_string());
        });
    

        io.socket()->on("ack_create_room", [&](sio::event& ev)
        {
            cout << "RESPONSE IS : " << ev.get_message()->get_string() << endl;

        });
    io.socket()->on("ack_join_room", [&](sio::event& ev)
    {
        cout << "A NEW PLAYER JOINED : " << ev.get_message()->get_string() << endl;
        players_name.push_back(ev.get_message()->get_string());
        if(players_name.size() == 2) 
        {
            usleep(2000000);
            InstanceHandler::Start();

        }

    });
    io.socket()->on("ack_start_game", [&](sio::event& ev)
        {
            cout << "START GAME WITH : " << ev.get_message()->get_string() << endl;
            
        });
    });
    while(1) usleep(500000);
    return 0;
}