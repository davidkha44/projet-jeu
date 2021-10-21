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
Entite ::~Entite(){}

EntiteTypeID Entite::getTypeId (){
	return typeID;
}
void Entite::setTypeID(EntiteTypeID newTypeID){
	typeID=newTypeID;
}

void Entite::setStatus (EntiteStatusID newStatus){
	StatusID=newStatus;
}

EntiteStats& Entite::getStats (){
return Stats;
}
bool const Entite :: isPersonnage (){
	return true;
}
    // Setters and Getters

EntiteStatusID Entite::getStatusID(){
	return StatusID;
}
void Entite::setEntiteStatusID(EntiteStatusID newStatusID){
	StatusID=newStatusID;
}

const EntiteStats& Entite:: getEntiteStats() const{
	return Stats;
}

void Entite:: setEntiteStats(const EntiteStats& EntiteStats){
	Stats=EntiteStats;
}
Direction Entite::getDirection() const{
	return direction;
}
void Entite:: setDirection(Direction newDirection){
	direction=newDirection;
}



