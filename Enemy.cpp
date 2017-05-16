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
    initialSpeed = sp;
    haveParticles = false;
    timeDead = new Time(2);
}

Enemy::~Enemy() {
    delete flashCooldown;
    delete cd;
    delete tri;
    flashCooldown = NULL;
    cd = NULL;
    tri = NULL;
}

void Enemy::flash(float dirX, float dirY){
    if(flashCooldown->isExpired()){
        Entity::move(flashRange*dirX, flashRange*dirY);
        flashCooldown->restart();
    }
}

void Enemy::setBlood(Texture *texture){
    /*****Particle*****/
    blood = new Particles(texture);
    blood->addParticle(Rect<float> (0, 0, 5, 5));
    blood->setProperties(20,0.25f,0.75f);
    blood->setParticleRotation(thor::Distributions::uniform(360.f, 0.f));
    blood->setParticleSpeed(thor::Distribution<sf::Vector2f> (sf::Vector2f(15.0f,-60.0f)));
    blood->setGravity(500.0f);
    haveParticles = true;
}

void Enemy::startBlood(float duration){
    if (haveParticles){
        blood->setParticlePosition(thor::Distributions::circle(sf::Vector2f(Entity::getCoordinate()->x+(Entity::getSize()->x/2), Entity::getCoordinate()->y+(Entity::getSize()->y/2)), 30));
        blood->start(duration);
    }
}

void Enemy::drawBlood(){
    if (haveParticles){
        blood->update();
        blood->draw();
    } 
}

void Enemy::die(){
    if(direction == 'r' || direction == 'a' || direction == 'c'){
        Entity::getAnimation()->changeAnimation("morirIzquierda",true);
        std::cout<<"izq"<<"\n";
    }else{
        Entity::getAnimation()->changeAnimation("morirDerecha",true);
        std::cout<<"der"<<"\n";
    }
    
}

void Enemy::damage(int dm){
    if (hp-dm <= 0){
        hp = 0;
        timeDead->start();
        die();
    }
    else hp -= dm;
}

void Enemy::move(float xDir, float yDir){
    Entity::move(xDir, yDir);
    if (xDir == 1 && yDir == 0) { //Derecha
        if (direction != 'r') {
            std::cout<<"de"<<"\n";
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        direction = 'r';
    } else if (xDir == -1 && yDir == 0) { //Izquierda
        if (direction != 'l') {
            std::cout<<"iz"<<"\n";
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direction = 'l';
    } else if (xDir == 0 && yDir == 1) { //Abajo
        if (direction != 'd') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        direction = 'd';
    } else if (xDir == 0 && yDir == -1) { //Arriba
        if (direction!='u') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        direction='u';
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
        if (direction!='a') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        direction='a';
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
        if (direction != 'b') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direction = 'b';
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
        if (direction != 'c') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
        }
        direction = 'c';
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
        if (direction != 'e') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direction='e';
    } else {
        if (direction != 'i'){
            Entity::getAnimation()->changeAnimation("idle", false);
        }
        direction='i';
    }
}

void Enemy::setFlashCooldown(Time *cooldown){ 
    flashCooldown = cooldown;
    maxFlashCooldown = cooldown->getTime();
    flashCooldown->start();
}

void Enemy::setAnimations(Texture *t, Rect<float> newRect){
    Entity::setSprite(t, newRect);
    if(type == 1){
        Entity::getAnimation()->addAnimation("idle", Coordinate(512, 0), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(512, 0), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(512, 128), 2, 0.5f);
        Entity::getAnimation()->addAnimation("morirDerecha", Coordinate(128, 1024), 1, 0.5f);
        Entity::getAnimation()->addAnimation("morirIzquierda", Coordinate(256, 1024), 1, 0.5f);
    }else if(type == 2){
        Entity::getAnimation()->addAnimation("idle", Coordinate(512, 256), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(512, 256), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(512, 384), 2, 0.5f);
        Entity::getAnimation()->addAnimation("morirDerecha", Coordinate(384, 1024), 1, 0.5f);
        Entity::getAnimation()->addAnimation("morirIzquierda", Coordinate(512, 1024), 1, 0.5f);
    }else if(type == 3){
        Entity::getAnimation()->addAnimation("idle", Coordinate(512, 512), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(512, 512), 2, 0.5f);
        Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(512, 640), 2, 0.5f);
        Entity::getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 1, 0.5f);
        Entity::getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 1, 0.5f);
        Entity::getAnimation()->addAnimation("morirDerecha", Coordinate(128, 1152), 1, 0.5f);
        Entity::getAnimation()->addAnimation("morirIzquierda", Coordinate(256, 1152), 1, 0.5f);
    }
    
    Entity::getAnimation()->initAnimator();
    Entity::getAnimation()->changeAnimation("idle", false); 
}

void Enemy::AI(Player* rath, HUD* hud){
    //float angle = tri->angle(rath->getCoordinate(), Entity::getCoordinate());
    float distance = tri->distance(rath->getCoordinate(), Entity::getCoordinate());
    float distanceIni = tri->distance(Entity::getCoordinate(), Entity::getInitialCoordinate());
    Coordinate dir = tri->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate ini = tri->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    if(freeze == true && (cd->isExpired() && hits == 1)){
        rath->setSpeed(rath->getSpeed()+slowDown);
        hits = 0;
        freeze = false;
    }
    if(distance < disPlayerEnemy && distance >= 100){
        if(distanceIni <= disEnemyHome && home == true){
            int num;
                
            move(dir.x, dir.y);
            if(type == 2){
                if(flashCooldown->isExpired()){
                    srand (time(NULL));
                    num = rand() % 3;
                }else{
                    num = 0;
                }
                if(num == 2){
                    if(((Entity::getCoordinate()->x+dir.x*flashRange) < rath->getCoordinate()->x) 
                        || ((Entity::getCoordinate()->x+dir.x*flashRange) > rath->getCoordinate()->x) 
                        || ((Entity::getCoordinate()->x+dir.x*flashRange) == rath->getCoordinate()->x)){
                        if(((Entity::getCoordinate()->y+dir.y*flashRange) < rath->getCoordinate()->y-128) 
                            || ((Entity::getCoordinate()->y+dir.y*flashRange) > rath->getCoordinate()->y+128)){
                            flash(dir.x, dir.y); 
                        } 
                    }else if(((Entity::getCoordinate()->y+dir.y*flashRange) < rath->getCoordinate()->y) 
                        || ((Entity::getCoordinate()->y+dir.y*flashRange) > rath->getCoordinate()->y) 
                        || ((Entity::getCoordinate()->y+dir.y*flashRange) == rath->getCoordinate()->y)){
                        if(((Entity::getCoordinate()->x+dir.x*flashRange) < rath->getCoordinate()->x-128) || ((Entity::getCoordinate()->x+dir.x*flashRange) > rath->getCoordinate()->x+128)){
                            flash(dir.x, dir.y); 
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
                if(distance < disPlayerEnemy && num == 2 && distance > disPlayerEnemy/5 && cd->isExpired()){
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
                    move(ini.x, ini.y);
                }else{
                    home = true;//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
                }
            }
        }
    }else if(distanceIni >= disEnemyHome || (home == false && distance > 128)){
            home = false;
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                move(ini.x, ini.y);
            }else{
                home = true;//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
            }
    }else if(distance > 128){
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
            move(ini.x, ini.y);
        }else{
            home = true;
        }
    }else if(distance < 100){
        if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
            move(ini.x, ini.y);
        }else{
            home = true;
        }
    }
}