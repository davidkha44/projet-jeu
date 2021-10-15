#include "Entite.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Entite :: Entite(EntiteTypeID id, int newX, int newY, EntiteStatusID status, EntiteStats stats){
	typeID=id;
	x=newX;
	y=newY;
	Status=status;
	Stats=stats;
}

EntiteStatusID Entite::getTypeId (){
	return StatusID;
}

void Entite::setStatus (EntiteStatusID newStatus){
	StatusID=newStatus;
}
void Entite:: setCharacterDeplacement (int newDeplacement){

}

EntiteStats& Entite::getStats (){
return Stats;
}
bool const Entite :: isPersonnage (){
	return true;
}
    // Setters and Getters


void Entite::setEntiteStatusID(EntiteStatusID newStatusID){
	StatusID=newStatusID;
}

void Entite:: setEntiteStats(const EntiteStats& EntiteStats){
	Stats=EntiteStats;
}
Direction Entite::getDirection() const{
	return direction;
};
void Entite:: setDirection(Direction newDirection){
	direction=newDirection;
}
EntiteStatusID Entite:: getStatusID(){
	return StatusID;
};

EntiteTypeID Entite::getTypeID() const{
	return typeID;
}
void Entite::setTypeID(EntiteTypeID newTypeID){
	typeID=newTypeID;
}