#include "Obstacle.h"

Obstacle::Obstacle(Coordinate position, Coordinate s, Texture *t, Rect<float> newRect) {
    initial = new Coordinate(position.x, position.y);
    
    hitbox = new Hitbox(position.x, position.y, s.x, s.y);
    hitbox->setPosition(position);
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(*initial);
    
    active = false;
}

Obstacle::~Obstacle() {
    delete hitbox;
    delete anim;
    delete initial;
    
    hitbox = NULL;
    anim = NULL;
    initial = NULL;
}

void Obstacle::setPosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
}

void Obstacle::setPosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
}