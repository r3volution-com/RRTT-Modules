#include "Gun.h"

Gun::Gun(Coordinate *position, Rect<float> *animRect, Texture *tex, int nS, float d) {
    width=animRect->w;
    height=animRect->h;
    hitbox = new Hitbox(position->x, position->y, animRect->w, animRect->h);
    gunAnimation = new Animation(tex, animRect, nS, d);
    gunAnimation->setPosition(position);
    setPosition(position);
}

Gun::~Gun() {
}

void Gun::setAttack(Bullet atk){
    attack = atk;
}

void Gun::doAttack(){
    //LLamar a singleton e instanciar el ataque
}

void Gun::setPosition(Coordinate *position){
    hitbox->setPosition(position);
    gunAnimation->setPosition(position);
}
void Gun::setRotation(float r){
    gunAnimation->setRotation(r);
}
void Gun::move(float x, float y){
    hitbox->move(x, y);
    gunAnimation->move(x, y);
}
void Gun::setActive() {
    if (active) active = false;
    else active = true;
}
