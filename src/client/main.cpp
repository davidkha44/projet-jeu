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

    Handler::HandlerCount = 0;
    Handler::HandlerCount++;
    PRINTLN(Handler::HandlerCount);
    MainFrame* mf = new MainFrame("TEST",800,600);

    
    return 0;
}
