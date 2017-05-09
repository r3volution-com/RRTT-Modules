#include "Boss.h"

Boss::Boss(Coordinate position, Coordinate size, float sp) : Enemy(position, size, sp) {
    state = 0;
    currentGun = -1;
    guns = new std::vector<Gun*>();
    attacking = false;
}

Boss::~Boss() {
    delete guns;
    guns = NULL;
}

void Boss::changeState(int s){
    if(s == 0){
        state = s;
    }else if(s == 1){
        state = s;
    }else if(s == 2){
        state = s;
    }
}

void Boss::gunAttack(){
    if (currentGun>-1 && attacking == false) {
        guns->at(currentGun)->doAttack();
        attacking = true;
        //ToDo pabloF: Traerte aqui la animacion de ataque con arma secundaria
    }
}

void Boss::addGun(Gun* gun){
    gun->setPosition(*Entity::getCoordinate());
    guns->push_back(gun);
    currentGun = guns->size()-1;
}

bool Boss::changeGun(int gun){
    if (gun >= 0 && gun < guns->size() && currentGun > -1){
        guns->at(currentGun)->setActive();
        currentGun = gun;
        guns->at(currentGun)->setActive();
        return true;
    } else return false;
}

void Boss::attackDone(){
    attacking = false;
}

void Boss::setPosition(Coordinate newCoor){
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (currentGun >= 0){
        guns->at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns->at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+50));
    }
}
void Boss::setPosition(float x, float y){
    Coordinate newCoor(x,y);
    Entity::getAnimation()->setPosition(newCoor);
    Entity::getHitbox()->setPosition(newCoor);
    if (currentGun >= 0){
        guns->at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns->at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
    }
}


void Boss::AI(Player* rath, HUD* hud){
   /* 
    float distance = tri->distance(rath->getCoordinate(), Entity::getCoordinate());
    float distanceIni = tri->distance(Entity::getCoordinate(), Entity::getInitialCoordinate());
    Coordinate *dir = tri->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate *ini = tri->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    
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
    
    if(state == 0){
        Entity::move()
    }else if(state == 1){
        
    }else if(state == 2){
    
    }*/
}