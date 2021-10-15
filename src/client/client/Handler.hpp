#include "Macro.hpp"


class Handler
{

    //STATIC(std::vector<void*> Handlers)
    
    public : 
        virtual void OnTurnBegin() = 0;
        virtual void OnTurnEnd() = 0;
        virtual void OnTurnBeginAsync() = 0;
        virtual void OnTurnEndAsync() = 0;
        virtual void RunAsync() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void ProcessInput() = 0;
};