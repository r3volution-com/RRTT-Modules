#include "Enemy.h"

Enemy::Enemy(Rect *enemyData, float sp): Entity (enemyData, sp){
    
}

Enemy::~Enemy() {
}

void Enemy::move(float x, float y){
    Entity::move(x, y);
}

void Enemy::flash(float dirX, float dirY){
    
}

void Enemy::die(){
    
}

void Enemy::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}

