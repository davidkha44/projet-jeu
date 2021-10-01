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
    MainFrame(std::string name,int h,int w); 
    void OnStart();
    void Tick();
    void Draw();
    void DrawActors();
    void DrawBGWorld();
    void DrawFGWorld();
    void DrawUI();
    

};