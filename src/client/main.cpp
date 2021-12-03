#include <iostream>
#include <client.h>
#include <engine.h>
#include "render.h"
#include "ai.h"
#include <state.h>
#include <string.h>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

//#include <state.h>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

int main(int argc,char* argv[])
{

    cout << "Hello" << endl;
    if(argc < 1)
        cout << "No args. Exit" << endl;

    if(!strcmp(argv[1],"state"))
    {
        cout << "Begin State Unit Tests" << endl;
        system("make test");
    }
    if(!strcmp(argv[1],"render"))
    {
        MainFrame* mf = FileHandler::LoadLaunchArgs("src/client/tables/LaunchArgs.csv");
        cout << "RENDER" << endl;
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));

        
        mf->Start();
        
    }
    if(!strcmp(argv[1],"engine"))
    {
        cout << "ENGINE : "<< getpid() << endl;
        MainFrame* mf = FileHandler::LoadLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
    }

    if(!strcmp(argv[1],"random_ai"))
    {
        RandomAI AI = RandomAI();
        vector <string> a1 = {"STD_ATTACK","0x1000","1","0","PATTERN_DIAMOND4","NET_CMD_ATTACK"};
        vector <string> a2 = {"STD_MOVE","0x2000","0","1","PATTERN_DIAMOND2","NET_CMD_MOVE"};
        vector <string> a3 = {"STD_INVOKE_CYAN","0x3000","1","0","PATTERN_CROSS","NET_CMD_INVOKE_CYAN"};
        Action A1 = Action(a1);;
        Action A2 = Action(a2);
        Action A3 = Action(a3);
        vector <engine::Action> a = {A1,A2,A3};
        Action A4 = AI.SelectRandomAction(a);
        cout << "Les actions sont : " << A1.Name() <<","<<A2.Name()<<","<<A3.Name() << endl;
        cout << "L'action sélectionnée est : " << A4.Name() << endl;
    }

    if(!strcmp(argv[1],"PROTOTYPE"))
    {
        cout << "INDISPONIBLE" << endl;
    }

    
    return 0;
}
