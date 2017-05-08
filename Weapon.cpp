#include "Weapon.h"
#include "Game.h"

Weapon::Weapon(Coordinate position, Coordinate size, float speed) {
    coor = new Coordinate(position);
    hitbox = new Hitbox(coor->x, coor->y, size.x, size.y);
    degreesPerTick = (60/Game::Instance()->iaPS)*speed;
    
    pie = new Pie(128, 40);
    pie->setColor(sf::Color(255, 255, 255, 100));
    pie->setOutline(5, sf::Color::White);
}

Weapon::~Weapon() {
    
}

void Weapon::setAnimation(Texture *tex, Rect<float> animRect){
    anim = new Animation(tex, animRect);
    anim->addAnimation("idle", Coordinate(animRect.x, animRect.y), 2, 1.0f);
    anim->addAnimation("attack", Coordinate(animRect.x, animRect.y+animRect.h), 2, 1.0f);
    anim->setPosition(*coor);
}

void Weapon::loadAttack(){
    if (lengthCount < (360/degreesPerTick)) {
        pie->getShape()->setPosition(coor->x, coor->y);
        pie->setFilledAngle(degreesPerTick);
        lengthCount++;
    }
}

void Weapon::doAttack(){
    anim->changeAnimation("attack", true);
    attackLength->restart((60/Game::Instance()->iaPS)*lengthCount);
}

void Weapon::setPosition(float x, float y){
    hitbox->setPosition(x, y);
    anim->setPosition(x, y);
}

void Weapon::setPosition(Coordinate coord){
    hitbox->setPosition(coord);
    anim->setPosition(coord);
}