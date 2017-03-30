#include "Coordinate.h"

Coordinate::Coordinate(float xC, float yC) {
    x = xC;
    y = yC;
}

Coordinate::Coordinate(const Coordinate& coor) {
    x = coor.x;
    y = coor.y;
}

void Coordinate::setCoordinate(float xC, float yC){
    x = xC;
    y = yC;
}

void Coordinate::setCoordinate(Coordinate coor){
    x = coor.x;
    y = coor.y;
}

Coordinate::~Coordinate(){
    
}