#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

    if(argc < 1)
    cout << "No args. Exit" << endl;

    if(!strcmp(argv[1], "listen"))
    {
        cout << "The server is listening" << endl;
    }

    return 0;
}