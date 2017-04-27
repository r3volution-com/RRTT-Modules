#include "Enemy.h"
#include "Player.h"
#include "Game.h"

Enemy::Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp): Entity (position, t, newRect, sp){
    flashRange=0;
    tri = new Trigonometry();
}

Enemy::~Enemy() {
    
}

void Enemy::flash(float dirX, float dirY){
    Entity::move(flashRange*dirX, flashRange*dirY);
    flashCooldown->restart();
}

void Enemy::die(){
    Entity::getAnimation()->changeAnimation("die",false);
}

void Enemy::damage(int dm){
    if (hp-dm <= 0) die();
    else hp -= dm;
}

void Enemy::move(float xDir, float yDir){
    Entity::move(xDir, yDir);
}

void Enemy::setFlashCooldown(Time *cooldown){ 
    flashCooldown = cooldown;
}



void Enemy::AI(Player* rath){
    float angle = tri->angle(rath->getCoordinate(), Entity::getCoordinate());
    float distance = tri->distance(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate *dir = tri->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate *ini = tri->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    if(distance < 300){
        Entity::setSpeed(4.0f);
        Entity::move(dir->x, dir->y);
    }else{
        Entity::setSpeed(7.0f);
        Entity::move(ini->x, ini->y);
    }
}