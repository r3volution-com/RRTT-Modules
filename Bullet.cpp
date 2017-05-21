#include "Bullet.h"
#include "libs/Time.h"

Bullet::Bullet(Coordinate size, float d, int t){
    hitbox = new Hitbox(0, 0, size.x, size.y);
    
    type = t;
    
    duration = d;
}

Bullet::~Bullet() {
    delete hitbox;
    delete anim;
    hitbox = NULL;
    anim = NULL;
}

void Bullet::setAnimation(Texture *t, Rect<float> newRect){
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(0,0);
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
