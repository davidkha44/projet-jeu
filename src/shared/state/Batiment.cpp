#include "Batiment.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Batiment::Batiment(int pv,int def,int batId,int dmg):pv(pv),def(def),batId(batId),dmg(dmg){}

//Batiment::~Batiment(){};

int Batiment::getPv(){
    return pv;
};

int Batiment::getId(){
    return batId;
};

int Batiment::getDef(){
    return def;
};

int Batiment::getDmg(){
    return dmg;
};

bool Batiment::isBatiment() const{
    return true;
}