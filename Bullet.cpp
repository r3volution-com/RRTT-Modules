#include "Bullet.h"
#include "libs/Time.h"

Bullet::Bullet(Coordinate position, Coordinate size, float d){
    coor = new InterpolatedCoordinate(position.x, position.y);
    hitbox = new Hitbox(position.x, position.y, size.x, size.y);
    hitbox->setPosition(position);
    initial = new Coordinate(position.x, position.y);
    
    duration = d;
}

Bullet::~Bullet() {
    delete coor;
    delete hitbox;
    delete anim;
    coor = NULL;
    hitbox = NULL;
    anim = NULL;
}

void Bullet::setAnimation(Texture *t, Rect<float> newRect){
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(*initial);
}

void Bullet::setPosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
}

void Bullet::setPosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
}
        
bool Bullet::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}