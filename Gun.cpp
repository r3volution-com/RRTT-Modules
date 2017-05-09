#include "Gun.h"
#include "libs/Time.h"
#include "Game.h"

Gun::Gun(Coordinate position, Coordinate size, float cd) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(position.x, position.y, size.x, size.y);
    bulletLoaded = false;
    gunCooldown = new Time(cd);
    gunCooldown->pause();
    maxCooldown = cd;
}

void Gun::setAnimation(Texture *tex, Rect<float> animRect){
    gunAnimation = new Animation(tex, animRect);
    gunAnimation->addAnimation("idle", Coordinate(animRect.x, animRect.y), 2, 1.0f);
    gunAnimation->addAnimation("attack", Coordinate(animRect.x, animRect.y+animRect.h), 2, 1.0f);
    gunAnimation->setPosition(*coor);
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
    bulletLifetime = new Time(0);
}

void Gun::doAttack(){
    if(bulletLoaded && !gunCooldown->isRunning()){
        //ToDo Sergio: LLamar a singleton e instanciar el ataque
        gunAnimation->changeAnimation("attack", true);
        
        gunCooldown->restart(maxCooldown);
        bulletLifetime->restart(attack->getDuration());
    }
}

void Gun::update(Coordinate position, float angle){
    gunAnimation->setRotation(angle);
    if (bulletLifetime->isRunning()){
        attack->getAnimation()->setRotation(angle-90);
        attack->setPosition(position);
    }
}

void Gun::setPosition(Coordinate position){
    coor->setCoordinate(position);
    hitbox->setPosition(position);
    gunAnimation->setPosition(position);
}

void Gun::setPosition(float x, float y){
    coor->setCoordinate(x, y);
    hitbox->setPosition(x, y);
    gunAnimation->setPosition(x, y);
}

void Gun::setActive() {
    if (active) active = false;
    else active = true;
}
