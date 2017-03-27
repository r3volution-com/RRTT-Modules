#include "Player.h"

Player::Player(Rect<float> *playerData, float sp) : Entity(playerData, sp){
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
    if (weaponLoaded) weapon->move(x, y);
    if (currentGun >= 0) guns->at(currentGun)->move(x, y);
}

void Player::addGun(Gun* gun){
    gun->setPosition(getCoordinate());
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
 
void Player::weaponAttack(Rect <float> *animRect){
    if (weaponLoaded) {
        weapon->doAttack(animRect);
        //ToDo: Mostrar animacion de ataque con arma primaria
    }
}

void Player::gunAttack(Rect <float> *animRect){
    if (currentGun>-1) {
        guns->at(currentGun)->doAttack(animRect);
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
