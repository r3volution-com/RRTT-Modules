#include "Weapon.h"
#include "Game.h"

Weapon::Weapon(Coordinate position, Coordinate size, float speed) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(coor->x, coor->y, size.x, size.y);
    degreesPerTick = (9)*speed;
    
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
        pie = new Pie(128, 40, ang);
        pie->setOutline(5, sf::Color::White);
        pie->setColor(sf::Color(255, 255, 255, 180));
        pie->setFilledAngle(90);
        attacking = true;
        lengthCount = 10;
    } 
    if (lengthCount <= (360/degreesPerTick)) {
        pie->getShape()->setPosition(coor->x, coor->y);
        //std::cout << "Fuera: " << lengthCount << "\n";
        pie->setFilledAngle(degreesPerTick);
        lengthCount++;
        
        if (lengthCount == 20) pie->setColor(sf::Color(255, 185, 185, 180));
        else if (lengthCount == 30) pie->setColor(sf::Color(255, 115, 115, 180));
        else if (lengthCount == 40) pie->setColor(sf::Color(255, 45, 45, 180));
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