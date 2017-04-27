#include "Boss.h"

Boss::Boss(Coordinate position, Texture *t, Rect<float> newRect, float sp) : Enemy(position, t, newRect, sp) {
    state = 0;
    currentGun = -1;
    guns = new std::vector<Gun*>();
}

Boss::~Boss() {
}

void Boss::changeState(int s){
    if(s == 0){
        state = s;
    }else if(s == 1){
        state = s;
    }else if(s == 2){
        state = s;
    }
}

void Boss::gunAttack(){
    if (currentGun>-1) {
        guns->at(currentGun)->doAttack();
        //ToDo pabloF: Mostrar animacion de ataque con arma secundaria
    }
}

void Boss::addGun(Gun* gun){
    gun->setPosition(*Entity::getCoordinate());
    guns->push_back(gun);
    currentGun = guns->size()-1;
}

bool Boss::changeGun(int gun){
    if (gun >= 0 && gun < guns->size() && currentGun > -1){
        guns->at(currentGun)->setActive();
        currentGun = gun;
        guns->at(currentGun)->setActive();
        return true;
    } else return false;
}
