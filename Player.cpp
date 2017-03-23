#include "Player.h"

Player::Player(Rect<float> *playerData, float sp) : Entity(playerData, sp){
    currentGun = -1;
}

Player::~Player() {
}

void Player::setWeapon(Gun *wP){
    weapon = wP;
}


void Player::move(float x, float y){
    Entity::move(x, y);
    weapon->move(x, y);
    if (currentGun >= 0) guns->at(currentGun);
}

bool Player::changeGun(int gun){
    if (gun >= 0 && gun < guns->size()){
        guns->at(currentGun)->setActive();
        currentGun = gun;
        guns->at(currentGun)->setActive();
        return true;
    } else return false;
}
 
void Player::weaponAttack(){
    weapon->attack();
}

void Player::gunAttack(){
    guns->at(currentGun)->attack();
}

void Player::flash(int dirX, int dirY){ //ToDo: isma
    
}

void Player::die(){ //ToDo: pabloL
    
}

void Player::respawn(){ //ToDo: pabloL
    setPosition(50.0, 50.0);
}

void Player::setFlashCooldown(int cooldown){
    maxFlashCooldown = cooldown;
    flashCooldown = cooldown;
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}
