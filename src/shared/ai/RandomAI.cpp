#include "engine.h"
#include "state.h"
#include "ai.h"
#include <iostream>
#include <stdlib.h>
#include "../../client/client/Macro.hpp"


using namespace state;
using namespace std;

GET_SET(ai::RandomAI,int,Num_Player);

engine::Action ai::RandomAI::SelectRandomAction(std::vector<engine::Action> Actions){
    int n = Actions.size();
    printf("n = %d",n);
    srand(time(0));
    int random = rand() % n;
    printf("random = %d",random);
    return Actions[random];
} 

ai::RandomAI::RandomAI(){
    _Num_Player = 1;
}

int ai::RandomAI::RandomInt(int* params)
{
    int min = params[0];
    int max = params[1];
    
    //return int entre min et max
    return 0;
}