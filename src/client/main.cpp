#include <iostream>
#include <client.h>

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
    Handler::Register<SelectionHandler>();
    Handler::RegisterMouseLeftEvent<SelectionHandler>();
    Handler::RegisterMouseRightEvent<SelectionHandler>();
    Handler::Register<WorldHandler>();
    
    cout << "Resource loaded" << endl;
    FileHandler::InitManagers("/home/ensea/PLT_proper/projet-jeu/src/client/tables/Managers.csv");
    

    cout << "MGR loaded" << Manager::Managers.size() << endl;
    for(Manager* m : Manager::Managers)
        std::cout << m->Name() << endl;

    MainFrame* mf;
    
    FileHandler::InitArgs(mf,"/home/ensea/PLT_proper/projet-jeu/src/client/tables/LaunchArgs.csv");
    Handler::RoutineTurnBegin();
    
    return 0;
}
