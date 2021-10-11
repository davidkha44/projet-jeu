#include "Handler.hpp"

Handler::Handler(std::string name)
{
    Name(name);
    ID(0xFEFE0000 + HandlerCount);
    HandlerCount++;
}

void Handler::Update()
{

}