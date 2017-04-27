#include "InterpolatedCoordinate.h"
#include <iostream>
#include "../Game.h"

InterpolatedCoordinate::InterpolatedCoordinate(float x, float y) {
    act = new Coordinate(x, y);
    last = new Coordinate(x, y);
    next = new Coordinate(x, y);
}

InterpolatedCoordinate::InterpolatedCoordinate(Coordinate firstCoord){
    act = new Coordinate(firstCoord.x, firstCoord.y);
    last = new Coordinate(firstCoord.x, firstCoord.y);
    next = new Coordinate(firstCoord.x, firstCoord.y);
}

InterpolatedCoordinate::~InterpolatedCoordinate() {
    delete act;
    delete last;
    delete next;
    act = NULL;
    last = NULL;
    next = NULL;
}

void InterpolatedCoordinate::setCoordinate(float x, float y){
    last->setCoordinate(act->x, act->y);
    next->setCoordinate(x, y);
}

void InterpolatedCoordinate::setCoordinate(Coordinate newCoord){
    last->setCoordinate(act->x, act->y);
    next->setCoordinate(newCoord.x, newCoord.y);
}

void InterpolatedCoordinate::move(float x, float y){
    last->setCoordinate(act->x, act->y);
    next->setCoordinate(act->x+x, act->y+y);
}

void InterpolatedCoordinate::move(Coordinate newCoord){
    last->setCoordinate(act->x, act->y);
    next->setCoordinate(act->x+newCoord.x, act->y+newCoord.y);
}

bool InterpolatedCoordinate::areEquals(float a, float b){
    return (fabs(a - b) < std::numeric_limits<float>::epsilon()*1000);
}

Coordinate InterpolatedCoordinate::getIC(){
    //if (!areEquals(act->x, next->x) || !areEquals(act->y, next->y)){
    //float newx = act->x+((next->x-last->x)/Game::Instance()->iaps);
    //float newy = act->y+((next->y-last->y)/Game::Instance()->iaps);
    
    float newx = (act->x*(1-Game::Instance()->interpolation))+(next->x*Game::Instance()->interpolation);
    float newy = (act->y*(1-Game::Instance()->interpolation))+(next->y*Game::Instance()->interpolation);
    
    //cout << newx << " " << newy << endl;
    
    act->setCoordinate(newx, newy);
       
    return *act;
}