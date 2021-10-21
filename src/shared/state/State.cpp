# include "State.h"
using namespace state;

State::State(){};
State::~State(){};
ElementTab& State::getGrid (){};
ElementTab& State::getChars (){};
int State::getTurn (){
    return turn;
}
bool State::getEnd (){
    return end;
}
void State::setTurn (int newTurn){
    turn=newTurn;
}
void State::setEnd (bool newEnd){
    end=newEnd;
}
void State::setWin(bool result){
    win=result;
}
bool State::getWin(){
    return win;
}
void State::initializeCharacters (){

};
void State::InitializeMoney (){

};