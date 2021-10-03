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

    sf::Vector2f frame_vs(800,600);
    sf::Vector2f rpos(50,0);
    sf::Vector2f rpos2(-50,0);
    int turn = 0;
    sf::VideoMode frame_vm(frame_vs.x,frame_vs.y);
    sf::RenderWindow win(frame_vm,"TITRE",sf::Style::Default);
    sf::RectangleShape rect(sf::Vector2f(20, 20));
    sf::RectangleShape rect2(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(frame_vs.x / 2, frame_vs.y / 2);
    rect.setOrigin(rpos);
    rect2.setFillColor(sf::Color::Green);
    rect2.setPosition(frame_vs.x / 2, frame_vs.y / 2);
    rect2.setOrigin(rpos);
    MainFrame* mf = new MainFrame("PLT");
    std::cout << mf->GetName() << endl;
    while(win.isOpen())
    {
        sf::Vector2f _rpos;
        if(turn % 2)
        _rpos = rpos;
        else
        _rpos = rpos2;
        ON_KEY(Z, 
        _rpos.y++;  
        RANGE(_rpos.y,-frame_vs.y/2,frame_vs.y/2);
        //printf("Current Pos %f :: %f \n",rpos.x,rpos.y);
        )
        ON_KEY(S, 
        _rpos.y--;  
        RANGE(_rpos.y,-frame_vs.y/2,frame_vs.y/2);
        //printf("Current Pos %f :: %f \n",rpos.x,rpos.y);
        )
        ON_KEY(D, 
        _rpos.x--;  
        RANGE(_rpos.x,-frame_vs.x/2,frame_vs.x/2);
        //printf("Current Pos %f :: %f \n",rpos.x,rpos.y);
        )
        ON_KEY(Q, 
        _rpos.x++;  
        RANGE(_rpos.x,-frame_vs.x/2,frame_vs.x/2);
        //printf("Current Pos %f :: %f \n",rpos.x,rpos.y);
        )
        if(turn % 2)
        {
            rect.setOrigin(_rpos.x,_rpos.y);
            rpos = _rpos;
        }
        else
        {
            rect2.setOrigin(_rpos.x,_rpos.y);
            rpos2 = _rpos;
        }
        

        
        ON_KEY_DBG(X,
        printf("Close Game !");
        win.close();
        )
        ON_KEY_DBG(M,
        printf("Change Turn !");
        turn++;
        )
        win.clear(COLOR(Blue));
        win.draw(rect);
        win.draw(rect2);
        win.display();
        
    }
        

    return 0;
}
