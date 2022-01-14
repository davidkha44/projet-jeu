#include "BehaviourLeaf.h"
#include "../../client/client/Macro.hpp"
#include "../engine.h"

ai::BehaviourLeaf::BehaviourLeaf(state::Actor* caster,state::Actor* target,std::string input)
{
    Caster = caster;
    Target = target;
    Input = input;
    Outcome = 0;
}

std::string ai::BehaviourLeaf::ToString()
{
    return std::string(Caster->Name() + "::"+Input+(Target ?" "+Target->Name() : " ")+" = "+std::to_string(Outcome));
}