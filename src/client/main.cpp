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
        cout << "RANDOM AI : "<< getpid() << endl;
        MainFrame* mf = FileHandler::LoadLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
    } 

    if(!strcmp(argv[1],"heuristic_ai"))
    {
        cout << "HEURISTIC AI : "<< getpid() << endl;
        MainFrame* mf = FileHandler::LoadLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
    }

    if(!strcmp(argv[1],"PROTOTYPE"))
    {
        cout << "INDISPONIBLE" << endl;
    }

    
    return 0;
}
