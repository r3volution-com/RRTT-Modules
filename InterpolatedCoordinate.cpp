#include "InterpolatedCoordinate.h"

InterpolatedCoordinate::InterpolatedCoordinate(float x, float y) {
    act = new Coordinate(x, y);
    last = new Coordinate(x, y);
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

Coordinate InterpolatedCoordinate::getIC(){
    //ToDo: Calcular coordenada interpolada
    return *act;
}