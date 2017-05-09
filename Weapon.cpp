#include "Weapon.h"
#include "Game.h"

Weapon::Weapon(Coordinate position, Coordinate size, float speed) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(coor->x, coor->y, size.x, size.y);
    degreesPerTick = speed;
    
    lengthCount = 10;
    attackLength = new Time(0);
    pie = NULL;
    attacking = false;
}

Weapon::~Weapon() {
    
}

void Weapon::loadAttack(char direction){
    if (!attacking){
        int ang = 0;
        if(direction == 'u'){
            ang = 270;
        } else if (direction == 'l'){
            ang = 180;
        } else if (direction == 'd'){
            ang = 90;
        }
        pie = new Pie(128, 40, ang); //ToDo: el 40 se debe pasar por algun lado
        pie->setOutline(5, sf::Color::White);
        pie->setColor(sf::Color(255, 255, 255, 180));
        pie->setFilledAngle(10);
        attacking = true;
    } 
    if (pie->getFilledAngle() <= 40) {//ToDo: el 40 se debe pasar por algun lado
        pie->getShape()->setPosition(coor->x, coor->y);
        pie->setFilledAngle(degreesPerTick);
        
        if (pie->getFilledAngle() == 20) pie->setColor(sf::Color(255, 185, 185, 180));
        else if (pie->getFilledAngle() == 30) pie->setColor(sf::Color(255, 115, 115, 180));
        else if (pie->getFilledAngle() == 40) pie->setColor(sf::Color(255, 45, 45, 180));
    }
}

int Weapon::releaseAttack(){
    attacking = false;
    delete pie;
    pie = NULL;
    attackLength->restart((60/Game::Instance()->iaPS)*lengthCount);
    return lengthCount;
}

void Weapon::shortAttack(char direction){
    attackLength->restart(0.25f); //ToDo: pasar el numero por constructor o algo asi?
    //ToDo: hitbox en la direccion
}

void Weapon::setPosition(Coordinate coord){
    coor->setCoordinate(coord);
    hitbox->setPosition(coord);
}

void Weapon::setPosition(float x, float y){
    coor->setCoordinate(x, y);
    hitbox->setPosition(x, y);
}