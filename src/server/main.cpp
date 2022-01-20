#include <iostream>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <sio_client.h>
#include <thread>
#include <engine.h>
#include <state.h>
#include <SFML/Graphics.hpp>


using namespace sio;
using namespace sf;
using namespace std;
using namespace state;
using namespace engine;

client io;
int iter = 0;


int main(int argc,char* argv[])
{
    std::vector<std::string> players_name;
    string endpoint(argv[1]);
    io.connect(endpoint + ":3000");
    NetMessageHandler::UserName = "HostServer";
    NetMessageHandler::IO = &io;

    io.set_open_listener([&]() {

        cout << "CONNECTED "  << endl;
    io.socket()->emit("req_create_user",NetMessageHandler::UserName);
        thread t([](){
            while(1)
            {
                io.socket()->emit("heartbeat",NetMessageHandler::UserName);  
                usleep(2000000);
                iter++;

            }
            });
        t.detach();
    io.socket()->on("req_net_cmd",[&](sio::event& ev)
        {
        cout << "NET_CMD IS : " << ev.get_message()->get_string() << endl;
        io.socket()->emit("ack_net_cmd", string("BackRoom::") + ev.get_message()->get_string());
        });
    
    io.socket()->emit("req_create_room", string("BackRoom;HostServer"));
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
            io.socket()->emit("req_start_game",string("BackRoom"));

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