#include "Enemy.h"

Enemy::Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp): Entity (position, t, newRect, sp){
    
}

Enemy::~Enemy() {
}

void Enemy::flash(float dirX, float dirY){
    
}

void Enemy::die(){
    
}

void Enemy::damage(int dm){
    if (hp-dm <= 0) die();
    else hp -= dm;
}

