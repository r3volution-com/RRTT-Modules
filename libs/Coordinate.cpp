#include "Coordinate.h"
#include <iostream>

Coordinate::Coordinate(float xC, float yC) {
    x = xC;
    y = yC;
}

Coordinate::Coordinate(const Coordinate& coor) {
    x = coor.x;
    y = coor.y;
}

Coordinate::Coordinate(sf::Vector2i coor){
    x = coor.x;
    y = coor.y;
}

Coordinate::Coordinate(sf::Vector2f coor){
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

bool Coordinate::operator == (const Coordinate &p) const {
    return this->x == p.x && this->y == p.y;
}

bool Coordinate::operator != (const Coordinate &p) const {
    return this->x != p.x || this->y != p.y;
}

Coordinate Coordinate::operator + (const Coordinate &p) const {
    return Coordinate(this->x+p.x, this->y+p.y);
}

Coordinate Coordinate::operator + (const float &p) const {
    return Coordinate(this->x+p, this->y+p);
}

/*std::ostream& operator << (std::ostream &o,const Coordinate &p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
} */