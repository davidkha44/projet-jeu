#include "Heuristics.h"
#include "../state.h"
#include "../engine.h"
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "../../client/client/Macro.hpp"



int ai::Heuristics::Norm1 (sf::Vector2i dir)
{
    return abs(dir.x)+abs(dir.y); 
}

int ai::Heuristics::Norm1 (int x, int y)
{
    return abs(x)+abs(y);    
}

int ai::Heuristics::Norm1(state::Actor* caster,state::Actor* target)
{
    return abs(caster->Position().x - target->Position().x) + abs(caster->Position().y - target->Position().y);
}

sf::Vector2i ai::Heuristics::Direction(state::Actor* caster,state::Actor* target)
{
    return sf::Vector2i(caster->Position().x - target->Position().x,caster->Position().y - target->Position().y);
}

int ai::Heuristics::MoveToward(int* args)
{
    //args 0 is the manager
    // args 1 is the id
    // args 2 3 is target pos
    state::Manager* mgr = state::Manager::GetMgrByID(args[0]);
    state::Actor* caster = (state::Actor*)mgr->GetByID(args[1]);
    //state::Actor* target = (state::Actor*)mgr->GetByPos(args[2],args[3]);
    engine::Action* mvtoward = engine::Action::Actions["STD_MOVE_TOWARD_POS"];
    std::vector<sf::Vector2i> poss = engine::Action::Reach(mvtoward,caster);
    sf::Vector2i fpos = poss[0];
    int i = 0;
    while(mgr->GetByPos(fpos))
        fpos = poss[i++];
        //for(sf::Vector2i v : poss)
        //std::cout << "POSS - " << caster->Position().x << "//" << caster->Position().y << "__"  << v.x << "::" << v.y  << "___" <<  Norm1(VECTOR_SUB(v,sf::Vector2i(args[2],args[3])))<< std::endl;
    int min = Norm1(VECTOR_SUB(poss[0],sf::Vector2i(args[2],args[3])));
    for(sf::Vector2i v : poss)
        if( !mgr->GetByPos(v) && min >  Norm1(VECTOR_SUB(v,sf::Vector2i(args[2],args[3]))))
            fpos = v;
    if(!mgr->GetByPos(fpos))
        caster->AssignPosition(fpos);
    //std::cout << "VECT : " << fpos.x << "::" << fpos.y << std::endl;
    

}
