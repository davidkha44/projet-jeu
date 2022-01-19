#include <iostream>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <sio_client.h>
#include <thread>
#include <engine.h>
#include <state.h>

using namespace sio;
using namespace std;
using namespace state;
using namespace engine;

client io;
int iter = 0;


int main(int argc,char* argv[])
{
    string endpoint(argv[1]);
    io.connect(endpoint + ":3000");

    io.set_open_listener([&]() {

        cout << "CONNECTED "  << endl;
    io.socket()->emit("req_create_user",string("HostServer"));
        thread t([](){
            while(1)
            {
                if(iter == 30) 
                    io.socket()->emit("req_start_game",string("BackRoom"));

                io.socket()->emit("heartbeat",string("HostServer"));  
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
    io.socket()->on("ack_start_game", [&](sio::event& ev)
        {
            cout << "START GAME WITH : " << ev.get_message()->get_string() << endl;
        });
    });
    while(1) usleep(500000);
    return 0;
}