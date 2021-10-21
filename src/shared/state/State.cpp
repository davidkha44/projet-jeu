# include "State.h"
using namespace state;

ElementTab& State::getGrid (){};
ElementTab& State::getChars (){};
int State::getTurn (){
    return turn;
}
int State::getEnd (){
    return end;
}
void State::setTurn (int newTurn){
    turn=newTurn;
}
void State::setEnd (bool result){
    win=result;
}
State::~State (){};
void State::initializeCharacters (){

};
void State::InitializeMoney (){

};