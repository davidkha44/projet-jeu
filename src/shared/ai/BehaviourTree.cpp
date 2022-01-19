#include "BehaviourTree.h"
#include "../../client/client/Macro.hpp"
#include "../engine.h"
#include "../ai.h"


ai::BehaviourTree::BehaviourTree(state::Actor* caster,state::Manager* mgr,engine::Script* bhv) : ai::Tree::Tree()
{
    Root = NULL;
    Caster = caster;
    Layer = mgr;
    Behaviour = bhv;
}

ai::Node* ai::BehaviourTree::RecursiveInsertCallback(void* args)
{
    ai::BehaviourLeaf* bl = (ai::BehaviourLeaf*)args;
    ai::BehaviourLeaf* new_bl = new ai::BehaviourLeaf(bl->Caster,NULL,bl->Input);
    void* params[4];
    params[0] = new_bl->Caster;
    params[1] = NULL;
    params[2] = (void*)new_bl->Input.c_str();
    new_bl->Outcome = ai::DeepAI::RateOutcome(params);
    return new ai::Node(new_bl);
}

/*ai::Node* ai::BehaviourTree::AlphaBetaParsing()
{
    ai::Node* currentNode = Root;

}*/



