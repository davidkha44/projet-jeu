#include "Handler.hpp"


void Handler::RoutineTurnBegin()
{
    for(std::function<void()> f : TurnBegin)
        f();
}
void Handler::RoutineMouseLeft(sf::Vector2i MousePos)
{
    for(std::function<void(sf::Vector2i)> f : MouseLeftEvents)
        f(MousePos);
}
void Handler::RoutineMouseRight(sf::Vector2i MousePos)
{
    for(std::function<void(sf::Vector2i)> f : MouseRightEvents)
        f(MousePos);
}
void Handler::Initialize()
{
    TurnBegin = *(new std::vector<std::function<void()>>);
}

