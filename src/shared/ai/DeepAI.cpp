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

int ai::DeepAI::RateOutcome(void** args)
{
    state::Actor* caster = (state::Actor*)args[0];
    state::Actor* target = (state::Actor*)args[1];
    std::string input = std::string((char*)args[2]);

    if(input == "Offense")
    {
        if(!caster->ActionOfType(1000))
            return 0;
        std::vector<state::Actor*> vicinity =  caster->ActionOfType(1000)->HostileVicinity(caster);
        if(!vicinity.size()) return 3;
        int max = caster->Property("DMG") - vicinity[0]->Property("DEF");
        for(state::Actor* actor : vicinity)
            if((caster->Property("DMG") - actor->Property("DEF")) > max)
                max = caster->Property("DMG") - actor->Property("DEF");
        return max;
    }
    if(input == "Defense")
        return 5;


}
