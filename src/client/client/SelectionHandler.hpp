#include "WorldHandler.hpp"


class SelectionHandler
{
    STATIC(std::vector<Manageable*> Selection);

    public :
        static void Add(Manageable*);
        static void Remove(Manageable*);
        static void OnTurnBeginAsync();
        static void OnTurnBegin();
        static void OnMouseLeft(sf::Vector2i MousePos);
        static void OnMouseRight(sf::Vector2i MousePos);
        static sf::Vector2i GetBGWpos(sf::Vector2i uv);
};