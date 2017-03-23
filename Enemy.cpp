#include "Enemy.h"

Enemy::Enemy(Rect<float> *enemyData, float sp): Entity (enemyData, sp){
    
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

