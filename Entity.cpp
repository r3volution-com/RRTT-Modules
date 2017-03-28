#include "Entity.h"

#include <iostream>

Entity::Entity(Coordinate position, Texture *t, Rect<float> newRect, float sp) {
    speed = sp;
    
    coor = new InterpolatedCoordinate(position.x, position.y);
    hitbox = new Hitbox(position.x, position.y, newRect.w, newRect.h);
    hitbox->setPosition(position);
    anim = new Animation(t, new Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(position);
}

Entity::~Entity() {
}

void Entity::move(float dirX, float dirY){
    coor->move(dirX*speed, dirY*speed);
    anim->setPosition(coor->getIC()->x, coor->getIC()->y);
    hitbox->setPosition(coor->getIC()->x, coor->getIC()->y);
}

bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}