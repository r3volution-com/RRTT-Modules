#include "Entity.h"

#include <iostream>

Entity::Entity(float x, float y, int w, int h, float sp) {
    coor = new InterpolatedCoordinate(x, y);
    hitbox = new Hitbox(x, y, w, h);
    width = w;
    height = h;
    speed = sp;
}

Entity::~Entity() {
}

void Entity::loadAnimation(Texture *t, int cX, int cY, int nS, float d){
    anim = new Animation(t, width, height, cX, cY, nS, d);
    anim->move(coor->getCoordinate().x, coor->getCoordinate().y);
}

void Entity::move(float dirX, float dirY){
    coor->setCoordinate(dirX*speed, dirY*speed);
    anim->move(coor->getIC().x, coor->getIC().y);
    hitbox->move(coor->getIC().x, coor->getIC().y);
}

bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}