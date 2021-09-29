#include "Macro.hpp"

class Handler
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(int,ID);
    STATIC(int HandlerCount);
    STATIC(std::vector<Handler> Handlers);
    
    public : 
        Handler(std::string n,)
};