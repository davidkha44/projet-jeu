#include "Macro.hpp"
#include "Manager.hpp"

class Actor : public Manageable
{
    ATTRIBUTE(int,HP)
    ATTRIBUTE(int,DMG)
    ATTRIBUTE(int,DEF)
    ATTRIBUTE(int,AP)
    ATTRIBUTE(int,MP)

    public :
        Actor(std::string name,std::string visual,int hp,int dmg,int def,int ap,int mp);
        Actor(std::vector<std::string> args);
        Actor(std::vector<std::string> args,sf::Vector2i pos);
        std::string Flush() override;
};