#include "Macro.hpp"
#include "Manager.hpp"

class World 
{
    ATTRIBUTE(std::string,Name)
    ATTRIBUTE(std::string,ResPath)
    ATTRIBUTE(sf::Vector2i,CellSize)
    ATTRIBUTE(sf::Vector2i,CellN)
    

    public :
    World(std::string name,std::string respath,int csx,int csy,int ncx,int ncy);
    void PrintWorldInfo();

    
};