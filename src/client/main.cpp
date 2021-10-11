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
using namespace state;

int main(int argc,char* argv[])
{
    string displayMessage("Hello !\n");
    cout << displayMessage;

    // Handler::HandlerCount = 0;
    // Handler::HandlerCount++;x
    // PRINTLN(Handler::HandlerCount);
    
    Manageable* bg_map = new Manageable("BG_MAP","/home/ensea/PLT/projet-jeu/rapport/map_simple2.png");
    cout << "Resource loaded" << endl;
    Manager* bg_mgr = new Manager("BG_MGR");
    cout << "MGR loaded" << Manager::Managers.size() << endl;
    bg_mgr->Add(bg_map);
    cout << "Resource added" << bg_mgr->Elements()->size() << endl;
    MainFrame* mf = new MainFrame("TEST",555,555);
    
    
    return 0;
}
