#include "EntiteStats.h"


using namespace state;

EntiteStats::EntiteStats(){};
EntiteStats::~EntiteStats(){};

int EntiteStats::getAtk(){
	return atk;
}

int EntiteStats::getDef(){
	return def;
}

int EntiteStats::getCost(){
    return cost;
}
int EntiteStats::getPV (){
    return PV;
}
int EntiteStats::getMag (){
    return mag;
}

int EntiteStats::getDeplacement (){
    return deplacement;
}
void EntiteStats::setDeplacement (int newDeplacement){
    deplacement=newDeplacement;
}
void EntiteStats::setPV (int newPV){
    PV=newPV;
}
void EntiteStats::setAtk (int newAtk){
    atk=newAtk;
}
void EntiteStats::setDef (int newDef){
    def=newDef;
}
void EntiteStats::setMag (int newMag){
    mag=newMag;
}
