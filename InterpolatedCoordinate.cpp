#include "InterpolatedCoordinate.h"

InterpolatedCoordinate::InterpolatedCoordinate(float x, float y) {
    act = new Coordinate(x, y);
    last = new Coordinate(x, y);
}

InterpolatedCoordinate::InterpolatedCoordinate(Coordinate* firstCoord){
    act = firstCoord;
    last = firstCoord;
}

InterpolatedCoordinate::~InterpolatedCoordinate() {
    delete act;
    delete last;
    act = NULL;
    last = NULL;
}

void InterpolatedCoordinate::setCoordinate(float x, float y){
    last->setCoordinate(act->x, act->y);
    act->setCoordinate(x, y);
}

void InterpolatedCoordinate::setCoordinate(Coordinate* newCoord){
    last->setCoordinate(act->x, act->y);
    act->setCoordinate(newCoord->x, newCoord->y);
}

Coordinate InterpolatedCoordinate::getIC(){
    //ToDo: Calcular coordenada interpolada
    return *act;
}