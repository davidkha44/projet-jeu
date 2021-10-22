#include "Macro.hpp"
#include <functional>
#include <SFML/Graphics.hpp>

class Handler
{  
    STATIC(std::vector<std::function<void()>> TurnBegin)
    STATIC(std::vector<std::function<void()>> TurnBeginAsync)
    STATIC(std::vector<std::function<void()>> TurnEndAsync)
    STATIC(std::vector<std::function<void()>> TurnEnd)
    public :
        template <class T> 
        static void RegisterTurnBeginEvent();
        template <class T> 
        static void RegisterTurnBeginAsyncEvent();
        template <class T> 
        static void RegisterTurnEndEvent();
        template <class T> 
        static void RegisterTurnEndAsyncEvent();

        
        static void RoutineTurnBegin();
        static void RoutineTurnBeginAsync();
        static void RoutineTurnEndAsync();
        static void RoutineTurnEnd();
        static void Initialize();
        static void* Exec(void* arg);
};
template <class T>
void Handler::RegisterTurnBeginEvent()
{
    TurnBegin.push_back(T::OnTurnBegin);
}
template <class T>
void Handler::RegisterTurnBeginAsyncEvent()
{
    TurnBeginAsync.push_back(T::OnTurnBeginAsync);
}







