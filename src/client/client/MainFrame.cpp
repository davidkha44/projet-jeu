#include "MainFrame.hpp"
#include <iostream>

MainFrame::MainFrame(std::string name,int h,int w)
{
    sf::Vector2f frame_vs(h,w);
    sf::VideoMode frame_vm(frame_vs.x,frame_vs.y);
    sf::RenderWindow win(frame_vm,name,sf::Style::Default);
    sf::Texture tex;
    sf::Sprite spr;
    Window(&win);
    Height(h);
    Width(w);
    OnStart();
    while(win.isOpen())
    {
        Window()->clear(sf::Color::Blue);
        for(Manager m : Manager::Managers)
        {
            std::cout << "DRAW MGR : " << m.Name() <<" //" << m.Elements()->size() << std::endl;
            m.Draw(Window());  
        }  
        Tick();

        Window()->display();
    }
            
}

void DrawBGWorld(Manager* bgmgr)
{
    for(Manageable* m : bgmgr->Elements())
        
}

void MainFrame::OnStart()
{

}

void MainFrame::Tick()
{
 
    ON_KEY_DBG(X,
    printf("Close Game !");
    Window()->close();
    )
    ON_KEY_DBG(M,
    printf("Change Turn !");
    )
}