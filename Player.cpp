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
}

void Player::die(){
    //ToDo pabloL: animacion de muerte
}

void Player::respawn(){
    hp = maxHP;
    //ToDo pabloL: animacion de respawn
    Entity::setPosition(500.0, 100.0); //ToDo pabloL: Sacar la posicion del Singleton
}

void Player::setFlashCooldown(int cooldown){ 
    //ToDo pabloL, sincronizar con el timer de HUD y hacer la otra funcion para añadir el tiempo actual del flash (que el hud saque la info de aqui)
    maxFlashCooldown = cooldown;
    flashCooldown = cooldown;
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}
