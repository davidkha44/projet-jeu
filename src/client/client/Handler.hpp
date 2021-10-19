#include "Macro.hpp"
#include <functional>
#include <SFML/Graphics.hpp>

class Handler
{  
    STATIC(std::vector<std::function<void()>> TurnBegin)
    STATIC(std::vector<std::function<void()>> TurnBeginAsync)
    STATIC(std::vector<std::function<void()>> TurnEndAsync)
    STATIC(std::vector<std::function<void()>> TurnEnd)
    STATIC(std::vector<std::function<void(sf::Keyboard::Key)>> KeyEvents)
    STATIC(std::vector<std::function<void(sf::Vector2i)>> MouseLeftEvents)
    STATIC(std::vector<std::function<void(sf::Vector2i)>> MouseRightEvents)
    public :
        template <class T> 
        static void OnTurnBegin();
        template <class T> 
        static void OnKey(sf::Keyboard::Key k);
        template <class T> 
        static void OnMouseLeft(sf::Vector2i MousePos);
        template <class T> 
        static void OnMouseRight(sf::Vector2i MousePos);
        template <class T> 
        static void OnTurnBeginAsync();
        template <class T> 
        static void Register();
        template <class T> 
        static void RegisterKeyboardEvent();
        template <class T> 
        static void RegisterMouseLeftEvent();
        template <class T> 
        static void RegisterMouseRightEvent();
        
        static void RoutineMouseLeft(sf::Vector2i MousePos);
        static void RoutineMouseRight(sf::Vector2i MousePos);
        static void RoutineTurnBegin();
        static void RoutineTurnBeginAsync();
        static void RoutineTurnEndAsync();
        static void RoutineTurnEnd();
        static void Initialize();
};

template <class T>
void Handler::OnTurnBegin()
{
    T::OnTurnBegin();
}
template <class T>
void Handler::OnMouseLeft(sf::Vector2i MousePos)
{
    T::OnMouseLeft(MousePos);
}
template <class T>
void Handler::Register()
{
    TurnBegin.push_back(T::OnTurnBegin);
}
template <class T>
void Handler::RegisterKeyboardEvent()
{
    KeyEvents.push_back(T::OnKey);
}
template <class T>
void Handler::RegisterMouseLeftEvent()
{
    MouseLeftEvents.push_back(T::OnMouseLeft);
}
template <class T>
void Handler::RegisterMouseRightEvent()
{
    MouseRightEvents.push_back(T::OnMouseRight);
}





