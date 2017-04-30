#include "Enemy.h"
#include "Player.h"
#include "Game.h"

Enemy::Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp): Entity (position, t, newRect, sp){
    flashRange=0;
    tri = new Trigonometry();
    cd = new Time(2.0f);
    home = true;
}

Enemy::~Enemy() {
    
}

void Enemy::flash(float dirX, float dirY){
    if(flashCooldown->isExpired()){
        Entity::move(flashRange*dirX, flashRange*dirY);
        flashCooldown->restart();
    }
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
    maxFlashCooldown = cooldown->getTime();
    flashCooldown->start();
}



void Enemy::AI(Player* rath){
    float angle = tri->angle(rath->getCoordinate(), Entity::getCoordinate());
    float distance = tri->distance(rath->getCoordinate(), Entity::getCoordinate());
    float distanceIni = tri->distance(Entity::getCoordinate(), Entity::getInitialCoordinate());
    Coordinate *dir = tri->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate *ini = tri->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    if(distance < 300){
        
        if(distanceIni <= 500 && home == true){
            Entity::setSpeed(4.0f);
            Entity::move(dir->x, dir->y);
            if(type == 2){
                int num;
                if(flashCooldown->isExpired()){
                    srand (time(NULL));
                    num = rand() % 3;
                }else{
                    num = 0;
                }
                if(num == 2){
                    if(((Entity::getCoordinate()->x+dir->x*flashRange) < rath->getCoordinate()->x-128) || ((Entity::getCoordinate()->x+dir->x*flashRange) > rath->getCoordinate()->x+128)){
                        if(((Entity::getCoordinate()->y+dir->y*flashRange) < rath->getCoordinate()->y-128) || ((Entity::getCoordinate()->y+dir->y*flashRange) > rath->getCoordinate()->y+128)){
                            flash(dir->x, dir->y); 
                        } 
                    }
                }
            }
            cd->start();
            if(Entity::getHitbox()->checkCollision(rath->getHitbox()) && cd->isExpired()){
                rath->damage(dmgHit);
                cd->restart();
            }
        }else if(distanceIni >= 500 || home == false){
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni != 0){
                Entity::setSpeed(7.0f);
                Entity::move(ini->x, ini->y);
            }else{
                home = true;
            }
        }
    }else if(distanceIni >= 500 || home == false){
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni != 0){
                Entity::setSpeed(7.0f);
                Entity::move(ini->x, ini->y);
            }else{
                home = true;
            }
    }else{
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni != 0){
            Entity::setSpeed(5.0f);
            Entity::move(ini->x, ini->y);
        }else{
            home = true;
        }
    }
}