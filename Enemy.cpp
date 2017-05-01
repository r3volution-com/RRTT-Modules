#include "Enemy.h"
#include "Player.h"
#include "Game.h"

Enemy::Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp): Entity (position, t, newRect, sp){
    flashRange=0;
    tri = new Trigonometry();
    cd = new Time(2.0f);
    home = true;
    freeze =  false;
    hits = 0;
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
    if(freeze == true || (cd->isExpired() && hits == 1)){
        rath->setSpeed(rath->getSpeed()+dmgFreeze);
        hits = 0;
        freeze = false;
    }
    if(distance < disPlayerEnemy){
        if(distanceIni <= disEnemyHome && home == true){
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
                    if(((Entity::getCoordinate()->x+dir->x*flashRange) < rath->getCoordinate()->x) || ((Entity::getCoordinate()->x+dir->x*flashRange) > rath->getCoordinate()->x) || ((Entity::getCoordinate()->x+dir->x*flashRange) == rath->getCoordinate()->x)){
                        if(((Entity::getCoordinate()->y+dir->y*flashRange) < rath->getCoordinate()->y-128) || ((Entity::getCoordinate()->y+dir->y*flashRange) > rath->getCoordinate()->y+128)){
                            flash(dir->x, dir->y); 
                        } 
                    }else if(((Entity::getCoordinate()->y+dir->y*flashRange) < rath->getCoordinate()->y) || ((Entity::getCoordinate()->y+dir->y*flashRange) > rath->getCoordinate()->y) || ((Entity::getCoordinate()->y+dir->y*flashRange) == rath->getCoordinate()->y)){
                        if(((Entity::getCoordinate()->x+dir->x*flashRange) < rath->getCoordinate()->x-128) || ((Entity::getCoordinate()->x+dir->x*flashRange) > rath->getCoordinate()->x+128)){
                            flash(dir->x, dir->y); 
                        } 
                    }
                }
            }
            if(type == 3){
                
            }
            if(Entity::getHitbox()->checkCollision(rath->getHitbox()) && cd->isExpired()){
                if(type == 3){
                    if(freeze == false && hits == 0){
                        hits++;
                        rath->setSpeed(rath->getSpeed()-dmgFreeze);//ToDo PabloL: Relentiza 3 puntos
                    }
                }
                //rath->damage(dmgHit);
                cd->restart();
            }
        }else{
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                Entity::move(ini->x, ini->y);
            }else{
                home = true;
            }
        }
    }else if(distanceIni >= disEnemyHome || home == false){
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                Entity::move(ini->x, ini->y);
            }else{
                home = true;//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
            }
    }else{
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
            Entity::move(ini->x, ini->y);
        }else{
            home = true;
        }
    }
}