#include "Observable.h"

using namespace state;


Observable::Observable(){};
Observable::~Observable(){};
void Observable::registerObserver (IObserver* observer){};
void Observable::notigyObservers (const StateEvent& e, State& state){};