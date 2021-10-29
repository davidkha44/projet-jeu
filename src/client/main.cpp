#include <iostream>
#include <client.h>
#include <string.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

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

    
    return 0;
}
    //     Handler::RegisterTurnBeginEvent<Actor>();
    // Handler::RegisterTurnBeginEvent<SelectionHandler>();
    // InputHandler::RegisterMouseLeftEvent<SelectionHandler>();
    // InputHandler::RegisterMouseRightEvent<SelectionHandler>();
    // Handler::RegisterTurnBeginEvent<WorldHandler>();
    // Handler::RegisterTurnBeginAsyncEvent<WorldHandler>();
    
    // cout << "Resource loaded" << endl;
    // FileHandler::InitManagers("/home/ensea/PLT_proper/projet-jeu/src/client/tables/Managers.csv");
    

    // cout << "MGR loaded" << Manager::Managers.size() << endl;
    // for(Manager* m : Manager::Managers)
    //     std::cout << m->Name() << endl;

    // MainFrame* mf;
    
    // FileHandler::InitArgs(mf,"/home/ensea/PLT_proper/projet-jeu/src/client/tables/LaunchArgs.csv");