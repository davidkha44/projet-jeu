#include "WorldHandler.hpp"


class SelectionHandler : public Handler
{
    STATIC(std::vector<Manageable*> Selection);

    public :
        SelectionHandler();
        static void Add(Manageable*);
        static void Remove(Manageable*);
        void OnTurnBegin() override;
        static sf::Vector2i GetBGWpos(sf::Vector2i uv);
};