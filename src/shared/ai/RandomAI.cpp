#include "engine.h"
#include "state.h"
#include "ai.h"
#include <iostream>
#include <stdlib.h>
#include "../../client/client/Macro.hpp"


using namespace state;
using namespace std;

int ai::RandomAI::RandomInt(int* params)
 {
     int min = params[0];
     int max = params[1];
     int n =rand()%(max-min)+min;
     //return int entre min et max
     return n;
 }

int ai::RandomAI::IsInRange(engine::Action* action,sf::Vector2i origin,sf::Vector2i pos)
{
    int x = origin.x;
    int y = origin.y;

    for(state::Actor* a : action->BasePattern()->Map())
    {
        if(pos.x == a->Position().x + origin.x && pos.y == a->Position().y + origin.y)
            return 1;
    }
    return 0;
}