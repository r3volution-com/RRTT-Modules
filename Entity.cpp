#include "Entity.h"

#include <iostream>

Entity::Entity(Rect<float> *newRect, float sp) {
    width = newRect->w;
    height = newRect->h;
    speed = sp;
    
    coor = new InterpolatedCoordinate(newRect->x, newRect->y);
    hitbox = new Hitbox(newRect->x, newRect->y, newRect->w, newRect->h);
}

Entity::~Entity() {
}

void Entity::loadAnimation(Texture *t, Coordinate *clipCoord, int nS, float d){
    anim = new Animation(t, new Rect<float>(clipCoord->x, clipCoord->y, width, height), nS, d);
    anim->setPosition(coor->getCoordinate());
}

void Entity::move(float dirX, float dirY){
    coor->setCoordinate(dirX*speed, dirY*speed);
    anim->move(coor->getIC().x, coor->getIC().y);
    hitbox->move(coor->getIC().x, coor->getIC().y);
}

bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}