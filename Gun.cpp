#include "Gun.h"

Gun::Gun(float x, float y, int w, int h, Animation *gA) {
    gunAnimation = gA;
    hitbox = new Hitbox(x, y, w, h);
    setPosition(x, y);
}

Gun::~Gun() {
}

void Gun::attack(){
    
}

void Gun::setPosition(float x, float y){
    hitbox->setPosition(x, y);
    gunAnimation->setPosition(x, y);
}
void Gun::move(float x, float y){
    hitbox->move(x, y);
    gunAnimation->move(x, y);
}
void Gun::setActive() {
    if (active) active = false;
    else active = true;
}