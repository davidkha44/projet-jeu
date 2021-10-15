#include "Element.h"

namespace state {
Element::Element(int x,int y,int id): x(x),y(y),id(id){};

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
}