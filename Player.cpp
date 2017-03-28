#include "Player.h"

Player::Player(Coordinate position, Texture *t, Rect<float> newRect, float sp) : Entity(position, t, newRect, sp){
    currentGun = -1;
    weaponLoaded = false;
    guns = new std::vector<Gun*>();
    flashRange=0;
}

Player::~Player() {
}

void Player::setWeapon(Gun *wP){
    weapon = wP;
    weaponLoaded = true;
}


void Player::move(float x, float y){
    Entity::move(x, y);
    if (weaponLoaded) weapon->getAnimation()->setPosition(*Entity::getCoordinate());
    if (currentGun >= 0) guns->at(currentGun)->getAnimation()->setPosition(*Entity::getCoordinate());
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
        //ToDo: Mostrar animacion de ataque con arma primaria
    }
}

void Player::gunAttack(){
    if (currentGun>-1) {
        guns->at(currentGun)->doAttack();
        //ToDo: Mostrar animacion de ataque con arma secundaria
    }
}

void Player::flash(float dirX, float dirY){ //ToDo: isma
    Entity::move(flashRange*dirX, flashRange*dirY);
}

void Player::die(){
    //ToDo pabloL: animacion de muerte
}

void Player::respawn(){
    hp = maxHP;
    //ToDo pabloL: animacion de respawn
    Entity::setPosition(500.0, 100.0);
}

void Player::setFlashCooldown(int cooldown){ 
    //ToDo pabloL, sincronizar con el timer de HUD
    maxFlashCooldown = cooldown;
    flashCooldown = cooldown;
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}
