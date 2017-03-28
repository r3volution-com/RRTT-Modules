#include "Gun.h"

Gun::Gun(Coordinate position, Rect<float> *animRect, Texture *tex) {
    hitbox = new Hitbox(position.x, position.y, animRect->w, animRect->h);
    gunAnimation = new Animation(tex, animRect);
    gunAnimation->addAnimation("idle", Coordinate(animRect->x, animRect->y), 2, 1.0f);
    gunAnimation->addAnimation("attack", Coordinate(animRect->x, animRect->y+animRect->h), 2, 1.0f);
    gunAnimation->setPosition(position);
    setPosition(position);
}

Gun::~Gun() {
    delete gunAnimation;
    delete hitbox;
    delete attack;
    gunAnimation = NULL;
    hitbox = NULL;
    attack = NULL;
}

void Gun::setAttack(Bullet *atk){
    attack = atk;
}

void Gun::doAttack(){
    //ToDo: LLamar a singleton e instanciar el ataque
    gunAnimation->changeAnimation("attack", true);
}

void Gun::setPosition(Coordinate position){
    hitbox->setPosition(position);
    gunAnimation->setPosition(position);
}

void Gun::setActive() {
    if (active) active = false;
    else active = true;
}
