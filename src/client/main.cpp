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
    
    Manageable* bg_map = new Manageable("BG_MAP","/home/ensea/PLT/projet-jeu/rapport/map_simple2.png");
    Manageable* bg_tile = new Manageable("BG_TILE","/home/ensea/PLT/projet-jeu/res/texture/Ground/grass2.png");
    Manageable* actor0 = new Manageable("ACTOR0","/home/ensea/PLT/projet-jeu/res/texture/Characters/Champions/Arthax.png");
    cout << "Resource loaded" << endl;
    FileHandler::InitManagers("/home/ensea/PLT/projet-jeu/src/client/tables/Managers.csv");
    

    // Manager* bg_mgr = new Manager("BG_MGR");
    // Manager* actor_mgr = new Manager("ACTOR_MGR");
    cout << "MGR loaded" << Manager::Managers.size() << endl;
    for(Manager* m : Manager::Managers)
        std::cout << m->Name() << endl;
    FileHandler::InitVisuals("/home/ensea/PLT/projet-jeu/src/client/tables/ManageablesVisuals.csv");
    FileHandler::InitWorld("/home/ensea/PLT/projet-jeu/src/client/maps/DefaultWorld.csv");
    //bg_mgr->Add(bg_map);
    //bg_mgr->Add(bg_tile);
    bg_tile->Sprite()->setScale(0.1,0.1);
    //actor_mgr->Add(actor0);
    //cout << "Resource added" << bg_mgr->Elements()->size() << endl;
    MainFrame* mf = new MainFrame("TEST",800,800);
    
    
    return 0;
}
