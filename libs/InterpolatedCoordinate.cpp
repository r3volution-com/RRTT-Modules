#include "InterpolatedCoordinate.h"
#include <iostream>
#include "../Game.h"

InterpolatedCoordinate::InterpolatedCoordinate(float x, float y) {
    act = new Coordinate(x, y);
    
    last = new Coordinate(x, y);
}

InterpolatedCoordinate::InterpolatedCoordinate(Coordinate firstCoord){
    act = new Coordinate(firstCoord.x, firstCoord.y);
    last = new Coordinate(firstCoord.x, firstCoord.y);
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

void InterpolatedCoordinate::setCoordinate(Coordinate newCoord){
    last->setCoordinate(act->x, act->y);
    act->setCoordinate(newCoord.x, newCoord.y);
}

void InterpolatedCoordinate::move(float x, float y){
    last->setCoordinate(act->x, act->y);
    act->setCoordinate(act->x+x, act->y+y);
}

void InterpolatedCoordinate::move(Coordinate newCoord){
    last->setCoordinate(act->x, act->y);
    act->setCoordinate(act->x+newCoord.x, act->y+newCoord.y);
}

Coordinate InterpolatedCoordinate::getIC(){
    float x = (last->x-act->x)/Game::Instance()->iaSpeed;
    float y = (last->y-act->y)/Game::Instance()->iaSpeed;

    return Coordinate(act->x+x,act->y+y);
}