#include "Macro.hpp"
#include <string>

class Handler
{
    ATTRIBUTE(std::string,Name)
    ATTRIBUTE(int,ID)
    STATIC(int HandlerCount)
    
    public : 
        Handler(std::string n);
        static Handler GetByID(int id);
        static Handler GetByName(std::string name);
        virtual void OnTurnBegin();
        virtual void OnTurnEnd();
        virtual void OnTurnBeginAsync();
        virtual void OnTurnEndAsync();
        virtual void RunAsync();
        virtual void Start();
        virtual void Update();
        virtual void ProcessInput();
};