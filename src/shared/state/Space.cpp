#include "Space.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Space::Space(SpaceTypeId id): Spaceid(id){};
Space::~Space(){};
bool const SpaceisSpace (){
    return true;
}

bool const Space:: equals (const Element& other){

}
SpaceTypeId const Space ::getSpaceTypeId (){
    return Spaceid;
}
void Space:: setSpaceTypeId (SpaceTypeId id){
    Spaceid=id;
}