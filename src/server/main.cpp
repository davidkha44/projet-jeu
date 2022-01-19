#include <iostream>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <sio_client.h>

using namespace sio;
using namespace std;



int main(int argc,char* argv[])
{
    client io;
    string endpoint(argv[1]);
    io.connect(endpoint + ":3000");

    io.set_open_listener([&]() {
        cout << "CONNECTED" << endl;
    io.socket()->emit("req_create_user",string("LandOwner;0xDEFEC8"));

    io.socket()->emit("req_create_room", string("BackRoom;LandOwner"));
    io.socket()->on("ack_create_room", [&](sio::event& ev)
        {
        cout << "RESPONSE IS : " << ev.get_message()->get_string() << endl;
        });
    });
    while(1) usleep(500000);
    return 0;
}