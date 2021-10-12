#include "MobileElement.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

MobileElement::MobileElement(int speed,int position):speed(speed),position(position){};


int MobileElement::getSpeed(){
    return speed;
};

int MobileElement::getPosition(){
    return position;
};

bool MobileElement::isStatic() const{
    return true;
}