#include "ActionLeaf.h"
#include "../state.h"
#include "../engine.h"
#include "ai.h"
#include "../../client/client/Macro.hpp"


ai::ActionLeaf::ActionLeaf(std::string name,state::Actor* caster,engine::Action* action)
{
    Name = name;
    Caster = caster;
    ActionPerformed = action;
    Weight = 0;
}
ai::ActionLeaf::ActionLeaf(std::string name,state::Actor* caster,engine::Action* action,int weight)
{
    Name = name;
    Caster = caster;
    ActionPerformed = action;
    Weight = weight;
}

std::string ai::ActionLeaf::ToString()
{
    return std::string(Caster->Name() + "::"+Name+"::"+std::to_string(Weight));
}