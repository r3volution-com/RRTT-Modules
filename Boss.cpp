#include "Boss.h"
#include "Game.h"

Boss::Boss(Coordinate position, Coordinate size, float sp, int lvl) : Enemy(position, size, sp) {
    state = 0;
    currentGun = -1;
    guns = new std::vector<Gun*>();
    attacking = false;
    onRange = false;
    level = lvl;
    initialSpeed = sp;
    dirFlash = new Coordinate(0,0);
    delay = new Time(0);
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
 
    float distance = Enemy::getTrigonometry()->distance(rath->getCoordinate(), Entity::getCoordinate());
    float distanceIni = Enemy::getTrigonometry()->distance(Entity::getCoordinate(), Entity::getInitialCoordinate());
    Coordinate dir = Enemy::getTrigonometry()->direction(rath->getCoordinate(), Entity::getCoordinate());
    Coordinate ini = Enemy::getTrigonometry()->direction(Entity::getInitialCoordinate(), Entity::getCoordinate());
    bool home = Enemy::getHome();
    
    Boss::getCurrentGun()->getGunCooldown()->start();
    
    if(distance < Enemy::getDisPlayerEnemy()){
        onRange = true;
    }else{
        onRange = false;
    }
    if(state == 0){ //Pasive
        if(onRange == true && distance >= 100){
            Entity::move(dir.x,dir.y);
            if(Enemy::getHP() >= 3*Enemy::getMaxHP()/5 || Enemy::getHP() <= Enemy::getMaxHP()/4 || defensive->isExpired()){
                state = 1;
                Boss::setSpeed(initialSpeed*1.2);
            }else{
                state = 2;
                Boss::setSpeed(initialSpeed*0.8);
            }
        }else if(distanceIni >= Enemy::getDisEnemyHome() || (home == false && distance > 128)){
            Enemy::setHome(home = false);
                if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10){
                    Entity::move(ini.x, ini.y);
                }else{
                    Enemy::setHome(home = true);//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
                }
        }else if(distance > 128){
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
                Entity::move(ini.x, ini.y);
            }else{
                Enemy::setHome(home = true);
            }
        }else if(distance < 100){
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
                Entity::move(ini.x, ini.y);
            }else{
                Enemy::setHome(home = true);
            }
        }
        
    }else if(state == 1){ //Aggressive
        if(onRange == true && distance >= 80){
            Entity::move(dir.x,dir.y);
            if(level == 1){
                float aux = (Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->width*Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->width);
                aux = aux + (Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->height*Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->height);
                aux = sqrt(aux);
                if(distance < aux*5){
                    if(!Boss::isAttacking() && Boss::getCurrentGun()->getGunCooldown()->isExpired()){
                        Boss::gunAttack();
                        Boss::getCurrentGun()->getBullet()->setPosition(*Boss::getCurrentGun()->getCoordinate());
                    }
                }
                if(Enemy::getHP() < Enemy::getMaxHP()/2 && Enemy::getHP() > Enemy::getMaxHP()/4 && !defensive->isExpired()){
                    state = 2;//ToDo: quizas almacenar en un vector el orden de los estados (con un addstatusorde o asi) para poder variar patrones de forma facil?
                }
            }else if(level == 2){
                
            }else if(level == 3){
                
            }
            
        }else{
            state = 0;
        }
    }else if(onRange == true && state == 2){ //Defensive
        Entity::move(dir.x,dir.y);
        defensive->start();
        if(distance >= 100 && !defensive->isExpired()){
            if(level == 1){
                delay->start();
                if(onDelay == false){
                    Coordinate aux = Enemy::getTrigonometry()->direction(rath->getCoordinate(), Entity::getCoordinate());
                    dirFlash = new Coordinate(aux.x,aux.y);
                    onDelay = true;
                    delay->restart();
                }
                if(delay->isExpired() && onDelay == true){
                    if(Enemy::getFlashCooldown()->isExpired()){
                        Enemy::flash(dirFlash->x, dirFlash->y);  
                        onDelay = false;
                    }
                }
                
            }else if(level == 2){
                
            }else if(level == 3){
                
            }
            
        }else{
            state = 0;
        }
    }
    if(Boss::getHitbox()->checkCollision(rath->getHitbox()) && Boss::getCooldownHit()->isExpired()){
        rath->damage(Boss::getDmg());
        hud->changeLifePlayer(rath->getHP());
        Boss::resetCooldownHit();
    }
}