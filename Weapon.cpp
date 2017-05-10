#include "Weapon.h"
#include "Game.h"

Weapon::Weapon(Coordinate position, Coordinate size, float speed) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(coor->x, coor->y, size.x, size.y);
    degreesPerTick = 9*speed;
    
    lengthCount = 0;
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
        pie = new Pie(64, 40, ang);
        pie->setColor(sf::Color(255, 255, 255, 0));
        pie->setFilledAngle(90);
        pie->getShape()->setPosition(coor->x, coor->y);
        lengthCount++;
        attacking = true;
        dir = direction;
    } else if (pie->getFilledAngle() <= 360) {
        pie->setFilledAngle(degreesPerTick);
        pie->getShape()->setPosition(coor->x, coor->y);
        
        if (pie->getFilledAngle() == 117){
            pie->setOutline(5, sf::Color::White);
            pie->setColor(sf::Color(255, 255, 255, 180));
            lengthCount++;
        } else if (pie->getFilledAngle() == 180){
            pie->setColor(sf::Color(255, 185, 185, 180));
            lengthCount++;
        } else if (pie->getFilledAngle() == 270) {
            pie->setColor(sf::Color(255, 115, 115, 180));
            lengthCount++;
        } else if (pie->getFilledAngle() == 360) {
            pie->setColor(sf::Color(255, 45, 45, 180));
            lengthCount++;
        }
    }
}

int Weapon::releaseAttack(){
    attacking = false;
    delete pie;
    pie = NULL;
    
    attackLength->restart(0.25f*lengthCount); //ToDo: pasar el numero por constructor o algo asi
    
    int lc = lengthCount;
    lengthCount = 0;
    return lc;
}

void Weapon::longAttackDmg(){
    if (!attackLength->isExpired()){
        //ToDo: hitbox thor, utilizar vector de coordenadas polares para rotar la hitbox en torno a un punto??
    }
}

void Weapon::shortAttack(char direction){
    attackLength->restart(0.25f); //ToDo: pasar el numero por constructor o algo asi
    //ToDo: hitbox en la direccion
}

void Weapon::setPosition(Coordinate coord){
    coor->setCoordinate(coord);
    hitbox->setPosition(coord);
    if (attacking) pie->getShape()->setPosition(coor->x, coor->y);
}

void Weapon::setPosition(float x, float y){
    coor->setCoordinate(x, y);
    hitbox->setPosition(x, y);
    if (attacking) pie->getShape()->setPosition(coor->x, coor->y);
}