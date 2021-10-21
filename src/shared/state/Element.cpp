#include "Element.h"

namespace state {
Element::Element(int x,int y,int id): x(x),y(y),id(id){};
Element::Element():x(0),y(0),id(0){};
Element:: ~Element (){};

int Element::getX (){
   return x;
}
int Element::getY (){
   return y;
}
void Element::setX (int newX){
    x=newX;
}
void Element::setY (int newY){ 
    y=newY;
}
int Element::getTypeID(){
    return id;
}
void Element::setTypeID(int newid){
    id=newid;
}
}