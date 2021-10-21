#include "ElementTab.h"
#include <vector>

using namespace state;
using namespace std;

ElementTab :: ElementTab(size_t width , size_t height ) : width(width),height(height){};

ElementTab::~ElementTab(){};
size_t const ElementTab :: getWidth (){
    return width;
}
size_t const ElementTab :: getHeight (){
    return height;
}

size_t ElementTab::add (Element* e){
    list.insert(list.end(), e);
    return list.size();
};

void ElementTab::resize (size_t w, size_t h){
    width=w;
    height=h;
}
Element* const ElementTab:: get (int i, int j ){
    
};
void ElementTab :: set (int i, int j , Element* e){
    
};