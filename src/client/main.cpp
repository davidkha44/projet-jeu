#include <iostream>
#include <client.h>
#include "render.h"
#include <state.h>
//#include "client/FileHandler.hpp"
#include <string.h>

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

    if(!strcmp(argv[1],"PROTOTYPE"))
    {
        // Handler::RegisterTurnBeginEvent<Actor>();
        // Handler::RegisterTurnBeginEvent<SelectionHandler>();
        // InputHandler::RegisterMouseLeftEvent<SelectionHandler>();
        // InputHandler::RegisterMouseRightEvent<SelectionHandler>();
        // Handler::RegisterTurnBeginEvent<WorldHandler>();
        // Handler::RegisterTurnBeginAsyncEvent<WorldHandler>();
    
        // cout << "Resource loaded" << endl;
        // //FileHandler::InitManagers("/home/ensea/PLT_proper/projet-jeu/src/client/tables/Managers.csv");
        // FileHandler::LoadCSVFile("src/client/tables/Managers.csv",&FileHandler::OnLoadManagerFromCSV);

        // cout << "MGR loaded" << Manager::Managers.size() << endl;
        // for(Manager* m : Manager::Managers)
        //     std::cout << m->Name() << endl;

        // MainFrame* mf;
    
        // FileHandler::InitArgs(mf,"src/client/tables/LaunchArgs.csv");
        // mf->OnStart();
    }

    
    return 0;
}
