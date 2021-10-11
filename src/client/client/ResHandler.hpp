#include "Macro.hpp"
#include "Handler.hpp"
#include "Manageable.hpp"

class ResHandler : public Handler
{
    ATTRIBUTE(std::string,BG_MAP);

    public :

    ResHandler();
    bool Load(Manageable m);
    bool Load(std::vector<Manageable> m);
};