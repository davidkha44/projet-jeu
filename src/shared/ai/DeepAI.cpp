#include "DeepAI.h"
#include "../state.h"
#include "../engine.h"
#include "ai.h"
#include "../../client/client/Macro.hpp"

#define OFFENSE_BIAS 10
#define DEFENSE_BIAS 2

int ai::DeepAI::ProcessActorTree(int* args)
{
    state::Manager* mgr = state::Manager::GetMgrByID(args[0]);
    state::Actor* caster = (state::Actor*)mgr->GetByID(args[1]);
    state::Actor* base_friendly = (state::Actor*)mgr->GetByID(args[2]);
    state::Actor* base_enemy = (state::Actor*)mgr->GetByID(args[3]);
    PRINTLN("PAT I");
    std::vector<state::Actor*> player0,player1,enemies;
    std::vector<ai::Node*> bl_self,bl_enemy,output;
    std::vector<std::vector<Node*>> leaves;
    PRINTLN("PAT II");
    


    for(state::Manageable* m : mgr->Elements())
        ((state::Actor*)m)->Property("OWNER") ? player1.push_back((state::Actor*) m) : player0.push_back((state::Actor*) m);
    enemies = caster->Property("OWNER") ? player1 : player0;
    ai::BehaviourTree* bhv_tree =  new ai::BehaviourTree(NULL,mgr,state::WorldHandler::Behaviour);
    bhv_tree->Inputs = std::map<std::string,std::string>(state::WorldHandler::Behaviour->BHV_TREES["actor_bhv"]->Inputs);
    bhv_tree->Caster = caster;
    bhv_tree->Root = new Node(new BehaviourLeaf(caster,NULL,"ROOT "+caster->Name()));
    PARSE_MAP(bhv_tree->Inputs,std::string,std::string, bl_self.push_back(new Node(new BehaviourLeaf(caster,NULL,it->first)));)
    for(state::Actor* en : enemies)
    {
        PARSE_MAP(bhv_tree->Inputs,std::string,std::string, bl_enemy.push_back(new Node(new BehaviourLeaf(en,NULL,it->first)));)
    }
    leaves.push_back(bl_self);
    leaves.push_back(bl_enemy);
    PRINTLN("PAT III");

    bhv_tree->Root->RecursiveInsertWithCallback<ai::BehaviourTree>(leaves,0);
    PRINTLN("PAT IV");
    
    output = bhv_tree->Level(bhv_tree->Level() - 1);
    ai::Node* choice = output[0];

    for(ai::Node* node : output)
        choice = (((ai::BehaviourLeaf*)node->Object)->Outcome > ((ai::BehaviourLeaf*)choice->Object)->Outcome) ? node : choice;
    ai::Node* node = choice;
    while(node && node->Parent != choice->Root())
        node = node->Parent;
    ai::BehaviourLeaf* nbf = (ai::BehaviourLeaf*)node->Object;
    
    state::Actor* target = (nbf->Input == "Offense") ? base_enemy : base_friendly; 
   
    std::vector<state::Actor*> vicinity =  caster->ActionOfType(1000)->HostileVicinity(caster);
    if(!vicinity.size())
    {
    PRINTLN("PAT V 0");
        
        args[2] = target->Position().x;
        args[3] = target->Position().y;
        ai::Heuristics::MoveToward(args);
        return 0;
    }
    else
    {
        state::Actor* t_target = vicinity[0];
        for(state::Actor* t_actor : vicinity)
            t_target = (t_actor->Property("HP") > t_target->Property("HP")) ? t_actor : t_target;
    PRINTLN("PAT V 1" << t_target->Name());
        args[0] = caster->ID();

        args[1] = t_target->Position().x;
        args[2] = t_target->Position().y;
        state::WorldHandler::Behaviour->RunFunction("Attack",args);
        return 0;
    }

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
        if(!vicinity.size()) return OFFENSE_BIAS;
        int max = caster->Property("DMG") - vicinity[0]->Property("DEF");
        for(state::Actor* actor : vicinity)
            if((caster->Property("DMG") - actor->Property("DEF")) > max)
                max = caster->Property("DMG") - actor->Property("DEF");
        max = (max < 0) ? -1*max : max;
        return max;
    }
    if(input == "Defense")
        return DEFENSE_BIAS;
}


