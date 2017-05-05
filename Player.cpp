#include "Player.h"

Player::Player(Coordinate position, Coordinate size, float sp) : Entity(position, size, sp){
    currentGun = -1;
    weaponLoaded = false;
    guns = new std::vector<Gun*>();
    flashRange=0;
    attacking = false;
}

Player::~Player() {
    delete weapon;
    delete guns;
    weapon = NULL;
    guns = NULL;
}

void Player::setAnimations(Texture *t, Rect<float> newRect){
    Entity::setSprite(t, newRect);
    Entity::getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrAbajo", Coordinate(0, 384), 4, 0.5f);
    Entity::getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 2, 0.5f);
    Entity::getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 2, 0.5f);
    Entity::getAnimation()->addAnimation("ataqueAbajo", Coordinate(0, 1024), 2, 0.5f);
    Entity::getAnimation()->addAnimation("ataqueArriba", Coordinate(0, 1152), 2, 0.5f);
    Entity::getAnimation()->initAnimator();
    Entity::getAnimation()->changeAnimation("idle", false); 
}

void Player::setWeapon(Gun *wP){
    weapon = wP;
    weaponLoaded = true;
}

void Player::move(float xDir, float yDir){
    if (xDir != 0 || yDir != 0) Entity::move(xDir, yDir);
    if (xDir == 1 && yDir == 0) { //Derecha
        if (state != 'r') {
            getAnimation()->changeAnimation("correrDerecha", false);
        }
        state = 'r';
    } else if (xDir == -1 && yDir == 0) { //Izquierda
        if (state != 'l') {
            getAnimation()->changeAnimation("correrIzquierda", false);
        }
        state = 'l';
    } else if (xDir == 0 && yDir == 1) { //Abajo
        if (state != 'd') {
            getAnimation()->changeAnimation("correrAbajo", false);
        }
        state = 'd';
    } else if (xDir == 0 && yDir == -1) { //Arriba
        if (state!='u') {
            getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
        if (state!='u') {
            getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
        if (state != 'l') {
            getAnimation()->changeAnimation("correrIzquierda", false);
        }
        state = 'l';
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
        if (state != 'r') {
            getAnimation()->changeAnimation("correrDerecha", false);
        }
        state = 'r';
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
        if (state != 'u') {
            getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else {
        getAnimation()->changeAnimation("idle", false);
    }
}

void Player::addGun(Gun* gun){
    gun->setPosition(*Entity::getCoordinate());
    guns->push_back(gun);
    currentGun = guns->size()-1;
}

bool Player::changeGun(int gun){
    if (gun >= 0 && gun < guns->size() && currentGun > -1){
        guns->at(currentGun)->setActive();
        currentGun = gun;
        guns->at(currentGun)->setActive();
        return true;
    } else return false;
}
 
void Player::weaponAttack(){
    if (weaponLoaded) {
        weapon->doAttack();
        attacking = true;
        //ToDo pabloF: Traerte aqui la animacion de ataque con arma primaria
    }
}

void Player::gunAttack(){
    if (currentGun>-1) {
        //guns->at(currentGun)->doAttack();
        attacking = true;
        //ToDo pabloF: Traerte aqui la animacion de ataque con arma secundaria
    }
}

void Player::flash(float dirX, float dirY){
    Entity::move(flashRange*dirX, flashRange*dirY);
    flashCooldown->restart();
}

void Player::die(){
    Entity::getAnimation()->changeAnimation("die",false);
}

void Player::respawn(Coordinate coor){
    hp = maxHP;
    Entity::getAnimation()->changeAnimation("respawn",false);
    Entity::setPosition(coor.x, coor.y); 
}

void Player::setFlashCooldown(Time *cooldown){ 
    flashCooldown = cooldown;
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}
void Player::setPosition(Coordinate newCoor){
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (weaponLoaded) weapon->setPosition(*Entity::getCoordinate());
    
    if (currentGun >= 0){
        guns->at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns->at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+50));
    }
}
void Player::setPosition(float x, float y){
    Coordinate newCoor(x,y);
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (weaponLoaded) weapon->setPosition(*Entity::getCoordinate());
    if (currentGun >= 0){
        guns->at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns->at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
    }
}
