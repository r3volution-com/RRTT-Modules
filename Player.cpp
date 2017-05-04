#include "Player.h"

Player::Player(Coordinate position, Texture *t, Rect<float> newRect, float sp) : Entity(position, t, newRect, sp){
    currentGun = -1;
    weaponLoaded = false;
    guns = new std::vector<Gun*>();
    flashRange=0;
}

Player::~Player() {
    delete weapon;
    delete guns;
    weapon = NULL;
    guns = NULL;
}

void Player::setWeapon(Gun *wP){
    weapon = wP;
    weaponLoaded = true;
}


void Player::move(float xDir, float yDir){
    Entity::move(xDir, yDir);
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
        //ToDo pabloF: Mostrar animacion de ataque con arma primaria
    }
}

void Player::gunAttack(){
    if (currentGun>-1) {
        guns->at(currentGun)->doAttack();
        //ToDo pabloF: Mostrar animacion de ataque con arma secundaria
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
        guns->at(currentGun)->setPosition(*Entity::getCoordinate());
        guns->at(currentGun)->getBullet()->setPosition(*Entity::getCoordinate());
    }
}
void Player::setPosition(float x, float y){
    Coordinate newCoor(x,y);
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (weaponLoaded) weapon->setPosition(*Entity::getCoordinate());
    if (currentGun >= 0){
        guns->at(currentGun)->setPosition(*Entity::getCoordinate());
        guns->at(currentGun)->getBullet()->setPosition(*Entity::getCoordinate());
    }
}