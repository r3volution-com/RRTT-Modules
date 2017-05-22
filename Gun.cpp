#include "Gun.h"
#include "libs/Time.h"
#include "Game.h"

Gun::Gun(float cd) {
    coor = new Coordinate(0,0);
    bulletLoaded = false;
    gunCooldown = new Time(cd);
    gunCooldown->pause();
    maxCooldown = cd;
}

void Gun::setAnimation(Texture *tex, Rect<float> animRect){
    gunAnimation = new Animation(tex, animRect);
    gunAnimation->addAnimation("idle", Coordinate(animRect.x, animRect.y), 1, 1.0f);
    gunAnimation->addAnimation("inversa", Coordinate(animRect.x+animRect.w, animRect.y), 1, 1.0f);
    gunAnimation->addAnimation("atras", Coordinate(animRect.x+(animRect.w*2), animRect.y), 1, 1.0f);    
    gunAnimation->initAnimator();    
    gunAnimation->changeAnimation("idle", false);
    gunAnimation->setPosition(*coor);
}

Gun::~Gun() {
    delete gunAnimation;
    delete attack;
    delete gunCooldown;
    delete coor;
    delete bulletLifetime;
    gunAnimation = NULL;
    attack = NULL;
    gunCooldown = NULL;
    coor = NULL;
    bulletLifetime = NULL;
}

void Gun::setAttack(Bullet *atk){
    bulletLoaded = true;
    attack = atk;
    bulletLifetime = new Time(0);
}

void Gun::doAttack(){
    if(bulletLoaded && !gunCooldown->isRunning()){
        //gunAnimation->changeAnimation("attack", true);
        gunCooldown->restart(maxCooldown);
        bulletLifetime->restart(attack->getDuration());
    }
    
}
 
void Gun::update(Coordinate position, float angle){
    gunAnimation->setRotation(angle);
    if (bulletLifetime->isRunning()){
        attack->getAnimation()->setRotation(angle-90);
        attack->getHitbox()->setPosition(position);
    }
}

void Gun::setPosition(Coordinate position){
    coor->setCoordinate(position);
    gunAnimation->setPosition(position);
}

void Gun::setPosition(float x, float y){
    coor->setCoordinate(x, y);
    gunAnimation->setPosition(x, y);
}

void Gun::setActive() {
    if (active) active = false;
    else active = true;
}

void Gun::derecha(){
    gunAnimation->changeAnimation("idle", true);
    gunAnimation->setOrigin(Coordinate(56,38));
    
}

void Gun::inversa(){
    gunAnimation->changeAnimation("inversa", true);
    gunAnimation->setOrigin(Coordinate(76,38));
}

void Gun::atras(){
    gunAnimation->changeAnimation("atras", true);
    gunAnimation->setOrigin(Coordinate(56,38));
}

void Gun::setCooldown(float aux){
    maxCooldown=aux;
}
