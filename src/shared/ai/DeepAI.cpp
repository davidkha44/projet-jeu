#include "DeepAI.h"
#include "../state.h"
#include "../engine.h"
#include "ai.h"
#include "../../client/client/Macro.hpp"


void ai::DeepAI::Process(state::Manager* mgr)
{
    std::vector<state::Actor*> player0,player1;
    std::vector<ai::ActionLeaf*> al0,al1;

    for(state::Manageable* m : mgr->Elements())
        ((state::Actor*)m)->Property("OWNER") ? player1.push_back((state::Actor*) m) : player0.push_back((state::Actor*) m);
        
}

void ai::DeepAI::ProcessActors(std::vector<state::Actor*> actors)
{

}
void ai::DeepAI::ProcessActor(state::Actor* actor)
{
    Tree* tree = new Tree(new Node((void*)actor));
    
    
}
