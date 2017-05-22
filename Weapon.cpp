#include "Weapon.h"
#include "Game.h"

Weapon::Weapon(Coordinate position, Coordinate size, float speed, float animationSpeed) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(coor->x, coor->y, size.x, size.y);
    
    pieResolution = 40;
    degreesPerTick = (360/pieResolution)*speed;
    pieRadius = 64; //ToDo: radio(64) y resolucion (40) por variable?
    
    lengthCount = 0;
    attackLength = new Time(0);
    pie = NULL;
    loadingAttack = false;
    isLong = false;
    
    dmg = 0;
    
    animSpeed = animationSpeed;
    
    vector = new thor::PolarVector2<float>(pieRadius, 0.f);
}

Weapon::~Weapon() {
    delete coor;
    delete hitbox;
    delete attackLength;
    delete pie;
    delete vector;
    
    coor = NULL;
    hitbox = NULL;
    attackLength = NULL;
    pie = NULL;
    vector = NULL;
}

void Weapon::loadAttack(char direction){
    if (attackLength->isExpired()){
        if (!loadingAttack){
            int ang = 0;
            if(direction == 'u'){
                ang = 225;
            } else if (direction == 'l'){
                ang = 135;
            } else if (direction == 'd'){
                ang = 45;
            } else if (direction == 'r'){
                ang = -45;
            }
            pie = new Pie(pieRadius, pieResolution, ang); 
            pie->setColor(sf::Color(255, 255, 255, 0));
            pie->setFilledAngle(90);
            pie->getShape()->setPosition(coor->x, coor->y);
            pie->setDirection(direction);
            lengthCount++;
            loadingAttack = true;
            dir = direction;
            vector->phi = 0;
        } else if (pie->getFilledAngle() <= 360) {
            pie->setFilledAngle(degreesPerTick);
            pie->getShape()->setPosition(coor->x + hitbox->hitbox->width/2, coor->y + hitbox->hitbox->height/2);

            if (pie->getFilledAngle() == 117){
                pie->setOutline(5, sf::Color::White);
                pie->setColor(sf::Color(255, 255, 255, 180));
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
}

int Weapon::releaseAttack(){
    if (loadingAttack){
        loadingAttack = false;
        
        if (lengthCount > 1) isLong = true;
        else shortAttack(pie->getDirection());

        delete pie;
        pie = NULL;

        attackLength->restart(animSpeed*lengthCount);

        int lc = lengthCount;
        lengthCount = 0;
        return lc;
    }
    return 0;
}

void Weapon::shortAttack(char direction){
    if(attackLength->isExpired() && !loadingAttack){
        isLong = false;
        attackLength->restart(animSpeed);
        if(direction == 'u'){
            hitbox->setPosition(coor->x, coor->y-hitbox->hitbox->height);
        } else if (direction == 'l'){
            hitbox->setPosition(coor->x-hitbox->hitbox->width, coor->y);
        } else if (direction == 'd'){
            hitbox->setPosition(coor->x, coor->y+hitbox->hitbox->height);
        } else if (direction == 'r'){
            hitbox->setPosition(coor->x+hitbox->hitbox->width, coor->y);
        }
    }
}

void Weapon::update(){
    if (!attackLength->isExpired()){
        if (isLong){
            vector->phi += (360/Game::Instance()->iaPS);
            sf::Vector2f pos = (sf::Vector2f)*vector;
            hitbox->setPosition(coor->x+pos.x, coor->y+pos.y);
        }
    } else {
        hitbox->setPosition(*coor);
    }
}

bool Weapon::detectCollisions(Hitbox *other){
    if (!attackLength->isExpired()){
        return hitbox->checkCollision(other);
    }
    return false;
}

void Weapon::setPosition(Coordinate coord){
    coor->setCoordinate(coord);
    hitbox->setPosition(coord);
    if (loadingAttack) pie->getShape()->setPosition(coor->x + hitbox->hitbox->width/2, coor->y + hitbox->hitbox->height/2);
}

void Weapon::setPosition(float x, float y){
    coor->setCoordinate(x, y);
    hitbox->setPosition(x, y);
    if (loadingAttack) pie->getShape()->setPosition(coor->x + hitbox->hitbox->width/2, coor->y + hitbox->hitbox->height/2);
}