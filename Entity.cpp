#include "Entity.h"

Entity::Entity(Coordinate position, Texture *t, Rect<float> newRect, float sp) {
    speed = sp;
    
    coor = new InterpolatedCoordinate(position.x, position.y);
    hitbox = new Hitbox(position.x, position.y, newRect.w, newRect.h);
    hitbox->setPosition(position);
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(position);
    initial = new Coordinate(position.x, position.y);
}

Entity::~Entity() {
    delete coor;
    delete hitbox;
    delete anim;
    coor = NULL;
    hitbox = NULL;
    anim = NULL;
}

void Entity::move(float dirX, float dirY){
    coor->move(dirX*speed, dirY*speed);
}

void Entity::setPosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
}

void Entity::setPosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
}
        
bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}