#include "Player.h"
#include "Level.h"
#include "Game.h"

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

void Player::setWeapon(Weapon *wP){
    weapon = wP;
    weaponLoaded = true;
}

void Player::move(float xDir, float yDir){
    if (xDir != 0 || yDir != 0) Entity::move(xDir, yDir);
    if (xDir == 1 && yDir == 0) { //Derecha
        if (state != 'r') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        state = 'r';
    } else if (xDir == -1 && yDir == 0) { //Izquierda
        if (state != 'l') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
        }
        state = 'l';
    } else if (xDir == 0 && yDir == 1) { //Abajo
        if (state != 'd') {
            Entity::getAnimation()->changeAnimation("correrAbajo", false);
        }
        state = 'd';
    } else if (xDir == 0 && yDir == -1) { //Arriba
        if (state!='u') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
        if (state!='u') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
        if (state != 'l') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
        }
        state = 'l';
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
        if (state != 'r') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        state = 'r';
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
        if (state != 'u') {
            getAnimation()->changeAnimation("correrArriba", false);
        }
        state='u';
    } else {
        if (state != 'i'){
            Entity::getAnimation()->changeAnimation("idle", false);
            state='i';
        }
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
 
void Player::weaponShortAttack(int angle){
    if (weaponLoaded && weapon->getTime()->isExpired()) {
        char direction = 'r';
        if(angle < 315 && angle > 225){ //Derecha
            Entity::getAnimation()->changeAnimation("ataqueDerecha", true);
            direction = 'r';
        } else if (angle < 225 && angle > 135){ //Arriba
            Entity::getAnimation()->changeAnimation("ataqueArriba", true);
            direction = 'u';
        } else if (angle < 135 && angle > 45){ //Izquierda
            Entity::getAnimation()->changeAnimation("ataqueIzquierda", true);
            direction = 'l';
        } else if (angle < 45 || angle > 315){ //Abajo
            Entity::getAnimation()->changeAnimation("ataqueAbajo", true);
            direction = 'd';
        }
        Entity::getAnimation()->queueAnimation("idle", false);
        weapon->shortAttack(direction);
    }
}

void Player::weaponChargeAttack(int initialAngle){
    if (weaponLoaded && weapon->getTime()->isExpired()) {
        char direction = 'r';
        if(initialAngle < 315 && initialAngle > 225){ //Derecha
            //ToDo: rotar shape
            direction = 'r';
        } else if (initialAngle < 225 && initialAngle > 135){ //Arriba
            //ToDo: rotar shape
            direction = 'u';
        } else if (initialAngle < 135 && initialAngle > 45){ //Izquierda
            //ToDo: rotar shape
            direction = 'l';
        } else if (initialAngle < 45 || initialAngle > 315){ //Abajo
            //ToDo: rotar shape
            direction = 'd';
        }
        weapon->loadAttack(direction);
    }
}

void Player::weaponReleaseAttack(){
    if (weaponLoaded) {
        int load = weapon->releaseAttack();
        std::cout << weapon->getDirection() << "\n";
        if(weapon->getDirection() == 'r'){ //Derecha
            if (load >= 1) Entity::getAnimation()->changeAnimation("ataqueDerecha", true);
            if (load >= 2) Entity::getAnimation()->queueAnimation("ataqueAbajo", true);
            if (load >= 3) Entity::getAnimation()->queueAnimation("ataqueIzquierda", true);
            if (load >= 4) Entity::getAnimation()->queueAnimation("ataqueArriba", true);
        } else if (weapon->getDirection() == 'u'){ //Arriba
            if (load >= 1) Entity::getAnimation()->changeAnimation("ataqueArriba", true);
            if (load >= 2) Entity::getAnimation()->queueAnimation("ataqueDerecha", true);
            if (load >= 3) Entity::getAnimation()->queueAnimation("ataqueAbajo", true);
            if (load >= 4) Entity::getAnimation()->queueAnimation("ataqueIzquierda", true);
        } else if (weapon->getDirection() == 'l'){ //Izquierda
            if (load >= 1) Entity::getAnimation()->changeAnimation("ataqueIzquierda", true);
            if (load >= 2) Entity::getAnimation()->queueAnimation("ataqueArriba", true);
            if (load >= 3) Entity::getAnimation()->queueAnimation("ataqueDerecha", true);
            if (load >= 4) Entity::getAnimation()->queueAnimation("ataqueAbajo", true);
        } else if (weapon->getDirection() == 'd'){ //Abajo
            if (load >= 1) Entity::getAnimation()->changeAnimation("ataqueAbajo", true);
            if (load >= 2) Entity::getAnimation()->queueAnimation("ataqueIzquierda", true);
            if (load >= 3) Entity::getAnimation()->queueAnimation("ataqueArriba", true);
            if (load >= 4) Entity::getAnimation()->queueAnimation("ataqueDerecha", true);
        }
        Entity::getAnimation()->queueAnimation("idle", false);
    }
}

void Player::gunAttack(){
    if (currentGun>-1 && attacking == false) {
        guns->at(currentGun)->doAttack();
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

void Player::respawn(Coordinate coor, int resp){
    hp = maxHP;
    Entity::getAnimation()->changeAnimation("respawn",false);
    Entity::setPosition(*Game::Instance()->getLevelState()->getLevel()->getRespawn(resp)); 
}

void Player::setFlashCooldown(Time *cooldown){ 
    flashCooldown = cooldown;
}

void Player::damage(int dmg){
    if (hp-dmg <= 0){
        hp -= dmg;
        die();
    }
    else hp -= dmg;
}
void Player::setPosition(Coordinate newCoor){
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (weaponLoaded) weapon->setPosition(*Entity::getCoordinate()+(getHitbox()->hitbox->width/2));
    
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

void Player::attackDone(){
    attacking = false;
}
