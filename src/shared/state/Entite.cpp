#include "Entite.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Entite :: Entite( int newX, int newY){
	x=newX;
	y=newY;
	
}
Entite ::~Entite(){}

EntiteTypeID Entite::getTypeID (){
	return typeID;
}
void Entite::setTypeID(EntiteTypeID newTypeID){
	typeID=newTypeID;
}

void Entite::setStatusID (EntiteStatusID newStatusID){
	StatusID=newStatusID;
}

EntiteStatusID Entite::getStatusID() {
	return StatusID;
}

EntiteStats& Entite::getEntiteStats(){
	return stats;
}

void Entite:: setEntiteStats(const EntiteStats& EntiteStats){
	stats=EntiteStats;
}

bool const Entite :: isPersonnage (){
	return true;
}

Direction const Entite::getDirection(){
	return Direction;
}
void Entite:: setDirection(Direction newDirection){
	direction=newDirection;
}



