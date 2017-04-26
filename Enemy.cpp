#include "Enemy.h"

Enemy::Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp): Entity (position, t, newRect, sp){
    flashRange=0;
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