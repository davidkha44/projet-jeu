#include <iostream>
#include <client.h>
#include "client/FileHandler.hpp"
#include <string.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

//#include <state.h>

using namespace std;


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
    if(!strcmp(argv[1],"PROTOTYPE"))
    {
        Handler::RegisterTurnBeginEvent<Actor>();
        Handler::RegisterTurnBeginEvent<SelectionHandler>();
        InputHandler::RegisterMouseLeftEvent<SelectionHandler>();
        InputHandler::RegisterMouseRightEvent<SelectionHandler>();
        Handler::RegisterTurnBeginEvent<WorldHandler>();
        Handler::RegisterTurnBeginAsyncEvent<WorldHandler>();
    
        cout << "Resource loaded" << endl;
        //FileHandler::InitManagers("/home/ensea/PLT_proper/projet-jeu/src/client/tables/Managers.csv");
        FileHandler::LoadCSVFile("/home/ensea/PLT/projet-jeu/src/client/tables/Managers.csv",&FileHandler::OnLoadManagerFromCSV);

        cout << "MGR loaded" << Manager::Managers.size() << endl;
        for(Manager* m : Manager::Managers)
            std::cout << m->Name() << endl;

        MainFrame* mf;
    
        FileHandler::InitArgs(mf,"/home/ensea/PLT/projet-jeu/src/client/tables/LaunchArgs.csv");
    }

    
    return 0;
}
