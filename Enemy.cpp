#include "Enemy.h"
#include "Player.h"
#include "Game.h"

Enemy::Enemy(Coordinate position, Coordinate size, float sp): Entity (position, size, sp){
    flashRange=0;
    tri = new Trigonometry();
    cd = new Time(2.0f);
    home = true;
    freeze =  false;
    hits = 0;
    flashRange = 0;
}

Enemy::~Enemy() {
    delete flashCooldown;
    delete cd;
    flashCooldown = NULL;
    cd = NULL;
}

void Enemy::flash(float dirX, float dirY){
    if(flashCooldown->isExpired()){
        Entity::move(flashRange*dirX, flashRange*dirY);
        flashCooldown->restart();
    }
}

void Enemy::die(){
    Entity::getAnimation()->changeAnimation("die",false);
    //std::cout << "muero" << "\n";
}

void Enemy::damage(int dm){
    if (hp-dm <= 0){
        hp -= dm;
        die();
    }
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



void Enemy::AI(Player* rath, HUD* hud){
    //float angle = tri->angle(rath->getCoordinate(), Entity::getCoordinate());
    float distance = tri->distance(rath->getCoordinate(), Entity::getCoordinate());
    float distanceIni = tri->distance(Entity::getCoordinate(), Entity::getInitialCoordinate());
    Coordinate *dir = tri->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate *ini = tri->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    if(freeze == true && (cd->isExpired() && hits == 1)){
        rath->setSpeed(rath->getSpeed()+slowDown);
        hits = 0;
        freeze = false;
    }
    if(distance < disPlayerEnemy && distance >= 100){
        if(distanceIni <= disEnemyHome && home == true){
            int num;
                
            Entity::move(dir->x, dir->y);
            if(type == 2){
                if(flashCooldown->isExpired()){
                    srand (time(NULL));
                    num = rand() % 3;
                }else{
                    num = 0;
                }
                if(num == 2){
                    if(((Entity::getCoordinate()->x+dir->x*flashRange) < rath->getCoordinate()->x) 
                        || ((Entity::getCoordinate()->x+dir->x*flashRange) > rath->getCoordinate()->x) 
                        || ((Entity::getCoordinate()->x+dir->x*flashRange) == rath->getCoordinate()->x)){
                        if(((Entity::getCoordinate()->y+dir->y*flashRange) < rath->getCoordinate()->y-128) 
                            || ((Entity::getCoordinate()->y+dir->y*flashRange) > rath->getCoordinate()->y+128)){
                            flash(dir->x, dir->y); 
                        } 
                    }else if(((Entity::getCoordinate()->y+dir->y*flashRange) < rath->getCoordinate()->y) 
                        || ((Entity::getCoordinate()->y+dir->y*flashRange) > rath->getCoordinate()->y) 
                        || ((Entity::getCoordinate()->y+dir->y*flashRange) == rath->getCoordinate()->y)){
                        if(((Entity::getCoordinate()->x+dir->x*flashRange) < rath->getCoordinate()->x-128) || ((Entity::getCoordinate()->x+dir->x*flashRange) > rath->getCoordinate()->x+128)){
                            flash(dir->x, dir->y); 
                        } 
                    }
                }
            }
            else if(type == 3){
                if(cd->isExpired()){
                    srand (time(NULL));
                    num = rand() % 3;
                }else{
                    num = 0;
                }
                if(distance < disPlayerEnemy && num == 2 && distance > disPlayerEnemy/2 && cd->isExpired()){
                    cd->restart();
                    freeze = true;
                    if(freeze == true && hits == 0){
                        hits++;
                        rath->setSpeed(rath->getSpeed()-slowDown);//ToDo PabloL: Relentiza 3 puntos
                    }
                }
            }
            if(Entity::getHitbox()->checkCollision(rath->getHitbox()) && cd->isExpired()){
                rath->damage(dmgHit);
                hud->changeLifePlayer(rath->getHP()-dmgHit);
                cd->restart();
            }
        }else{
            if(distanceIni >= disEnemyHome || home == false){
            home = false;
                if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                    Entity::move(ini->x, ini->y);
                }else{
                    home = true;//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
                }
            }
        }
    }else if(distanceIni >= disEnemyHome || home == false && distance > 128){
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                Entity::move(ini->x, ini->y);
            }else{
                home = true;//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
            }
    }else if(distance > 128){
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
            Entity::move(ini->x, ini->y);
        }else{
            home = true;
        }
    }else if(distance < 100){
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
            Entity::move(ini->x, ini->y);
        }else{
            home = true;
        }
    }
}