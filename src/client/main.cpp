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
    
    
    cout << "Resource loaded" << endl;
    FileHandler::InitManagers("/home/ensea/PLT/projet-jeu/src/client/tables/Managers.csv");
    

    // Manager* bg_mgr = new Manager("BG_MGR");
    // Manager* actor_mgr = new Manager("ACTOR_MGR");
    cout << "MGR loaded" << Manager::Managers.size() << endl;
    for(Manager* m : Manager::Managers)
        std::cout << m->Name() << endl;
    FileHandler::InitVisuals("/home/ensea/PLT/projet-jeu/src/client/tables/ManageablesVisuals.csv");
    //bg_mgr->Add(bg_map);
    //bg_mgr->Add(bg_tile);

    //actor_mgr->Add(actor0);
    //cout << "Resource added" << bg_mgr->Elements()->size() << endl;
    MainFrame* mf;
    FileHandler::InitArgs(mf,"/home/ensea/PLT/projet-jeu/src/client/tables/LaunchArgs.csv");
    
    
    return 0;
}
