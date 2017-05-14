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

void Boss::move(float xDir, float yDir){
    Entity::move(xDir, yDir);
    if (xDir == 1 && yDir == 0) { //Derecha
        if (dirSprite != 'r') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
            guns->at(currentGun)->derecha();
        }
        dirSprite = 'r';
    } else if (xDir == -1 && yDir == 0) { //Izquierda
        if (dirSprite != 'l') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
            guns->at(currentGun)->inversa();
        }
        dirSprite = 'l';
    } else if (xDir == 0 && yDir == 1) { //Abajo
        if (dirSprite != 'd') {
            Entity::getAnimation()->changeAnimation("correrAbajo", false);
            guns->at(currentGun)->inversa();
        }
        dirSprite = 'd';
    } else if (xDir == 0 && yDir == -1) { //Arriba
        if (dirSprite!='u') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns->at(currentGun)->atras();                
        }
        dirSprite='u';
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
        if (dirSprite!='a') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns->at(currentGun)->atras();                
        }
        dirSprite='a';
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
        if (dirSprite != 'b') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
            guns->at(currentGun)->inversa();
        }
        dirSprite = 'b';
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
        if (dirSprite != 'c') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
            guns->at(currentGun)->derecha();
        }
        dirSprite = 'c';
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
        if (dirSprite != 'e') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns->at(currentGun)->atras();
        }
        dirSprite='e';
    } else {
        if (dirSprite != 'i'){
            Entity::getAnimation()->changeAnimation("idle", false);
            guns->at(currentGun)->derecha();
            dirSprite='i';
        }
    }
}

void Boss::flash(float xDir, float yDir){
    std::cout<<"si"<<"\n";
    if (xDir == 1 && yDir == 0) { //Derecha
            Entity::getAnimation()->changeAnimation("flashDerecha", true);
    } else if (xDir == -1 && yDir == 0) { //Izquierda
            Entity::getAnimation()->changeAnimation("flashIzquierda", true);
    } else if (xDir == 0 && yDir == 1) { //Abajo
            Entity::getAnimation()->changeAnimation("flashAbajo", true);
    } else if (xDir == 0 && yDir == -1) { //Arriba
            Entity::getAnimation()->changeAnimation("flashArriba", true);
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
            Entity::getAnimation()->changeAnimation("flashArriba", true);
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
            Entity::getAnimation()->changeAnimation("flashIzquierda", true);
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
            Entity::getAnimation()->changeAnimation("flashDerecha", true);
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
            Entity::getAnimation()->changeAnimation("flashArriba", true);
    }
    Entity::getAnimation()->queueAnimation("idle",false);
    Enemy::flash(xDir, yDir);
}

void Boss::setAnimations(Texture *t, Rect<float> newRect){
    Entity::setSprite(t, newRect);
    if(level == 1){
        Entity::getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 5.0f);
        Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
        Entity::getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
        Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 4, 0.5f);
        Entity::getAnimation()->addAnimation("correrAbajo", Coordinate(0, 384), 4, 0.5f);
        Entity::getAnimation()->addAnimation("flashDerecha", Coordinate(0, 768), 1, 0.25f);
        Entity::getAnimation()->addAnimation("flashIzquierda", Coordinate(0, 896), 1, 0.25f);
        Entity::getAnimation()->addAnimation("flashAbajo", Coordinate(0, 1024), 1, 0.25f);
        Entity::getAnimation()->addAnimation("flashArriba", Coordinate(0, 1152), 1, 0.25f);
    }else if(level == 2){
        
    }else if(level == 3){
        
    }
    
    Entity::getAnimation()->initAnimator();
    Entity::getAnimation()->changeAnimation("idle", false); 
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
            move(dir.x,dir.y);
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
                    move(ini.x, ini.y);
                }else{
                    Enemy::setHome(home = true);//ToDo PabloL: Por que coño caaaasi  nuuuuuuuuunca llega al punto exacto?
                }
        }else if(distance > 128){
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
                move(ini.x, ini.y);
            }else{
                Enemy::setHome(home = true);
            }
        }else if(distance < 100){
            if(Entity::getCoordinate() != Entity::getInitialCoordinate() && distanceIni > 10 ){
                move(ini.x, ini.y);
            }else{
                Enemy::setHome(home = true);
            }
        }
        
    }else if(state == 1){ //Aggressive
        if(onRange == true && distance >= 80){
            move(dir.x,dir.y);
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
        move(dir.x,dir.y);
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
                        flash(dirFlash->x, dirFlash->y);
                        
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