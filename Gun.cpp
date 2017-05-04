#include "Gun.h"
#include "libs/Time.h"
#include "Game.h"

Gun::Gun(Coordinate position, Rect<float> animRect, Texture *tex) {
    hitbox = new Hitbox(position.x, position.y, animRect.w, animRect.h);
    gunAnimation = new Animation(tex, animRect);
    gunAnimation->addAnimation("idle", Coordinate(animRect.x, animRect.y), 2, 1.0f);
    gunAnimation->addAnimation("attack", Coordinate(animRect.x, animRect.y+animRect.h), 2, 1.0f);
    gunAnimation->setPosition(position);
    bulletLoaded = false;
}

Gun::~Gun() {
    delete gunAnimation;
    delete hitbox;
    delete attack;
    delete gunCooldown;
    gunAnimation = NULL;
    hitbox = NULL;
    attack = NULL;
    gunCooldown = NULL;
}

void Gun::setAttack(Bullet *atk){
    bulletLoaded = true;
    attack = atk;
}

void Gun::doAttack(){
    if(gunCooldown->isExpired()){
        //ToDo Sergio: LLamar a singleton e instanciar el ataque
        gunAnimation->changeAnimation("attack", true);
        
        gunCooldown->restart();
    }
}

void Gun::setPosition(Coordinate position){
    hitbox->setPosition(position);
    gunAnimation->setPosition(position);
}

void Gun::setGunCooldown(Time* gc){
    gunCooldown = gc;
}

void Gun::setActive() {
    if (active) active = false;
    else active = true;
}
