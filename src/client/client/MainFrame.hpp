#include "Macro.hpp"
#include <SFML/Graphics.hpp>

class MainFrame
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(std::string,Path);
    ATTRIBUTE(sf::RenderWindow*,Window);
    ATTRIBUTE(int,Height);
    ATTRIBUTE(int,Width);
    ATTRIBUTE(int,Framerate);


    public : 
    MainFrame(std::string name,int h,int w)
    {
        sf::Vector2f frame_vs(h,w);
        sf::VideoMode frame_vm(frame_vs.x,frame_vs.y);
        sf::RenderWindow win(frame_vm,name,sf::Style::Default);
        Window(&win);
        Height(h);
        Width(w);
        OnStart();
        while(win.isOpen())
        {
            Tick();
            Window()->clear(sf::Color::Blue);
            Window()->display();
        }
            
    }

    public : 
    void OnStart()
    {

    }

    void Tick()
    {
        
        ON_KEY_DBG(X,
        printf("Close Game !");
        Window()->close();
        )
        ON_KEY_DBG(M,
        printf("Change Turn !");
        )
    }
    

};