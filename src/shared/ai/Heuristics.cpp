#include "Heuristics.h"
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>

int distance(int x, int y, int x2, int y2){
    int sum=abs(x-x2);
    sum+=abs(y-y2);
    return (sum);
}

std::vector<std::vector<int>> ListeDistance(std::vector<sf::Vector2i> L,int xb,int yb){
    std::vector<std::vector<int>> Ld;
    for(double i=0;i<L.size();i++){
        Ld.push_back({L[i].x,L[i].y,distance(L[i].x,L[i].y,xb,yb)});
    }
    return Ld;
}
sf::Vector2i minList(std::vector<std::vector<int>> L){
    sf::Vector2i minP;
    int dm=L[0][2];
    for(double i=0; i<L.size();i++){
        if(L[i][2]<dm){
            dm=L[i][2];
            minP.x=L[i][0];
            minP.y=L[i][1];
        }
    }
    return minP;
}

int Norm1 (sf::Vector2i dir){
    return (abs(dir.x)+abs(dir.y)); 
};
int Norm1 (int x, int y){
    return (abs(x)+abs(y));    
}