#include "Personnage.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Personnage::Personnage(int pv,PersonnageTypeId persoId,int def,int atk,int cost):pv(pv),persoId(persoId),def(def),atk(atk),cost(cost){
};

//Personnage::~Personnage(){};

int Personnage::getPv(){
    return pv;
};
int Personnage::getId(){
	return persoId;
};

int Personnage::getAtk(){
	return atk;
};

int Personnage::getDef(){
	return def;
};

int Personnage::getCost(){
    return cost;
};

bool Personnage::isPersonnage() const{
	return true;
}