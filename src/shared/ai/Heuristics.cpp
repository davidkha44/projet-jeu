#include "Heuristics.h"
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>



int Norm1 (sf::Vector2i dir)
{
    return abs(dir.x)+abs(dir.y); 
}

int Norm1 (int x, int y)
{
    return abs(x)+abs(y);    
}

int Norm1(state::Actor* caster,state::Actor* target)
{
    return abs(caster->Position().x - target->Position().x) + abs(caster->Position().y - target->Position().y);
}

sf::Vector2i Direction(state::Actor* caster,state::Actor* target)
{
    return sf::Vector2i(caster->Position().x - target->Position().x,caster->Position().y - target->Position().y);
}

