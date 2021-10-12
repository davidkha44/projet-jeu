#include "Handler.hpp"
#include "Manageable.hpp"

class SelectionHandler : public Handler
{
    ATTRIBUTE(std::vector<Manageable>,Selection);

    public :
        SelectionHandler();
        void Add(Manageable);
        void Remove(Manageable);
        void OnTurnBegin() override;
        static sf::Vector2i GetBGWpos(sf::Vector2i uv)
        {
            float csize = 555/20;
            sf::Vector2i output(uv.x/csize,uv.y/csize);
            return output;
        }
};