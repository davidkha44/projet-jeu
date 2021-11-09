#include "Macro.hpp"
#include <SFML/Graphics.hpp>

class MainFrame
{
    ATTRIBUTE(std::string,Name)
    ATTRIBUTE(std::string,Path)
    ATTRIBUTE(int,Height)
    ATTRIBUTE(int,Width)
    ATTRIBUTE(int,Framerate)

    STATIC(sf::RenderWindow* Window)
    

    public :
    MainFrame(std::string name,int h,int w); 
    void OnStart();
    void Tick();
    void Draw();

    

};