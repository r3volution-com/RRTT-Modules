#include "Entity.h"

Entity::Entity(Coordinate position, Coordinate size, float sp) {
    speed = sp;
    
    coor = new InterpolatedCoordinate(position.x, position.y);
    hitbox = new Hitbox(position.x, position.y, size.x, size.y);
    hitbox->setPosition(position);
    initial = new Coordinate(position.x, position.y);
}

Entity::~Entity() {
    delete coor;
    delete hitbox;
    delete anim;
    delete initial;
    coor = NULL;
    hitbox = NULL;
    anim = NULL;
    initial = NULL;
}

void Entity::setSprite(Texture *t, Rect<float> newRect){
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(*initial);
}

void Entity::move(float dirX, float dirY){
    coor->move(dirX*speed, dirY*speed);
}

void Entity::move(float dirX, float dirY, float sp){
    coor->move(dirX*sp, dirY*sp);
}

void Entity::setPosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
    coor->setCoordinate(newCoor);
}

void Entity::setPosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
    coor->setCoordinate(x, y);
}

void Entity::updatePosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
}

void Entity::updatePosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
}
        
bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}