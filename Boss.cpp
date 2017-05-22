#include "Boss.h"
#include "Game.h"

Boss::Boss(Coordinate position, Coordinate size, float sp) : Enemy(position, size, sp) {
    state = 0;
    actualState = -1;
    currentGun = -1;
    attacking = false;
    onRange = false;
    initialSpeed = sp;
    dirFlash = new Coordinate(0,0);
    delay = new Time(0.5f);
    start = false;
    nextState = false;
    angle = 0;
    stateClock = new Time(0);
}

Boss::~Boss() {
    delete stateClock;
    delete delay;
    delete dirFlash;
    stateClock = NULL;
    delay = NULL;
    dirFlash = NULL;
    states.clear();
    for (int i=0; i<guns.size(); i++){
        delete guns.at(i);
        guns.at(i) = NULL;
    }
    guns.clear();
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
        guns.at(currentGun)->doAttack();
        attacking = true;
        //ToDo pabloF: Traerte aqui la animacion de ataque con arma secundaria
    }
}

void Boss::addGun(Gun* gun){
    gun->setPosition(*Entity::getCoordinate());
    guns.push_back(gun);
    currentGun = guns.size()-1;
    guns.at(currentGun)->getGunCooldown()->start();
}

bool Boss::changeGun(int gun){
    if (gun >= 0 && gun < guns.size() && currentGun > -1 && gun != currentGun){
        guns.at(currentGun)->setActive();
        currentGun = gun;
        guns.at(currentGun)->setActive();
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
            guns.at(currentGun)->derecha();
        }
        dirSprite = 'r';
    } else if (xDir == -1 && yDir == 0) { //Izquierda
        if (dirSprite != 'l') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
            guns.at(currentGun)->inversa();
        }
        dirSprite = 'l';
    } else if (xDir == 0 && yDir == 1) { //Abajo
        if (dirSprite != 'd') {
            Entity::getAnimation()->changeAnimation("correrAbajo", false);
            guns.at(currentGun)->inversa();
        }
        dirSprite = 'd';
    } else if (xDir == 0 && yDir == -1) { //Arriba
        if (dirSprite!='u') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns.at(currentGun)->atras();                
        }
        dirSprite='u';
    } else if (xDir == 1 && yDir == -1){ //Arriba derecha
        if (dirSprite!='a') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns.at(currentGun)->atras();                
        }
        dirSprite='a';
    } else if (xDir == -1 && yDir == 1){ //Abajo izquierda
        if (dirSprite != 'b') {
            Entity::getAnimation()->changeAnimation("correrIzquierda", false);
            guns.at(currentGun)->inversa();
        }
        dirSprite = 'b';
    } else if (xDir == 1 && yDir == 1){ //Derecha abajo
        if (dirSprite != 'c') {
            Entity::getAnimation()->changeAnimation("correrDerecha", false);
            guns.at(currentGun)->derecha();
        }
        dirSprite = 'c';
    } else if (xDir == -1 && yDir == -1){ //Izquierda arriba
        if (dirSprite != 'e') {
            Entity::getAnimation()->changeAnimation("correrArriba", false);
            guns.at(currentGun)->atras();
        }
        dirSprite='e';
    } else {
        if (dirSprite != 'i'){
            Entity::getAnimation()->changeAnimation("idle", false);
            guns.at(currentGun)->derecha();
            dirSprite='i';
        }
    }
}

void Boss::flash(float xDir, float yDir){
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
    Entity::getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 5.0f);
    Entity::getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 512), 4, 0.5f);
    Entity::getAnimation()->addAnimation("correrAbajo", Coordinate(0, 384), 4, 0.5f);
    Entity::getAnimation()->addAnimation("flashDerecha", Coordinate(0, 640), 1, 0.25f);
    Entity::getAnimation()->addAnimation("flashIzquierda", Coordinate(128, 640), 1, 0.25f);
    Entity::getAnimation()->addAnimation("flashAbajo", Coordinate(256, 640), 1, 0.25f);
    Entity::getAnimation()->addAnimation("flashArriba", Coordinate(384, 640), 1, 0.25f);
    Entity::getAnimation()->initAnimator();
    Entity::getAnimation()->changeAnimation("idle", false); 
}

void Boss::setPosition(Coordinate newCoor){
    Entity::setPosition(newCoor);
    if (currentGun >= 0){
        guns.at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns.at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+50));
    }
}

void Boss::setPosition(float x, float y){
    Entity::setPosition(x, y);
    if (currentGun >= 0){
        guns.at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns.at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
    }
}

void Boss::updatePosition(Coordinate newCoor){
    Entity::updatePosition(newCoor);
    if (currentGun >= 0){
        guns.at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns.at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+50));
    }
}

void Boss::updatePosition(float x, float y){
    Entity::updatePosition(x, y);
    if (currentGun >= 0){
        guns.at(currentGun)->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
        guns.at(currentGun)->getBullet()->setPosition(Coordinate(Entity::getCoordinate()->x+60, Entity::getCoordinate()->y+40));
    }
}

void Boss::damage(int dm){
    if (Boss::getHP()-dm <= 0){
        Boss::setHP(0);
        //die();
    }
    else Boss::setHP(Boss::getHP()-dm);
    if(actualDmg + dm >= Enemy::getMaxHP()/states.size()){
        nextState = true;
        actualDmg = 0;
    }else{
        actualDmg += dm;
    }
}

void Boss::addState(int s){
    states.push_back(s);
}

void Boss::addRandomState(int from, int to){
    int num = rand() % (to-from+1) + from;
    states.push_back(num);
}

void Boss::changeState(){
    if(stateClock->isExpired() || nextState == true){
        actualState++;
        if(actualState >= states.size()){
            actualState = 0;
        }
        state = states.at(actualState);
        stateClock->restart(timeState);
        nextState = false;
    }
    if(state == 0 && start == true){
        state = states.at(actualState);
        start = false;
    }
}
void Boss::AI(Player* rath, HUD* hud){
    float distance = Enemy::getTrigonometry()->distance(*rath->getCoordinate(), *Entity::getCoordinate());
    float distanceIni = Enemy::getTrigonometry()->distance(*Entity::getCoordinate(), *Entity::getInitialCoordinate());
    Coordinate dir = Enemy::getTrigonometry()->direction(*rath->getCoordinate(), *Entity::getCoordinate());
    Coordinate ini = Enemy::getTrigonometry()->direction(*Entity::getInitialCoordinate(), *Entity::getCoordinate());
    bool home = Enemy::getHome();
    
    Boss::getCurrentGun()->getGunCooldown()->start();
    
    if(distance < Enemy::getDisPlayerEnemy()){
        onRange = true;
    }else{
        onRange = false;
    }
    
    
    if(Boss::getHitbox()->checkCollision(rath->getHitbox()) && Boss::getCooldownHit()->isExpired()){
        rath->damage(Boss::getDmg());
        hud->changeLifePlayer(rath->getHP());
        Boss::resetCooldownHit();
    }
    
    if(state == 0){ //Pasive
        if(onRange == true && distance >= 100){
            changeState();
            start = true;
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
        }else if(Boss::getHitbox()->checkCollision(rath->getHitbox())){
            Enemy::getState()->update();
            Entity::setSpeed(0);
        }
    }
    
    if(onRange == true && !Boss::getHitbox()->checkCollision(rath->getHitbox())){
        
        Boss::setDmgHit(Boss::getInitialDmg());
        Entity::setSpeed(Boss::getInitialSpeed());
        
        if(state == 1){
            if(guns.size() > 1 && currentGun != 0){
                currentGun = 0;
                changeGun(currentGun);
            }
            move(dir.x,dir.y);
            float aux = (Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->width*Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->width);
            aux = aux + (Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->height*Boss::getCurrentGun()->getBullet()->getHitbox()->hitbox->height);
            aux = sqrt(aux);
            if(distance < aux*5){
                if(!Boss::isAttacking() && Boss::getCurrentGun()->getGunCooldown()->isExpired()){
                    Boss::gunAttack();
                    Boss::getCurrentGun()->getBullet()->setPosition(*Boss::getCurrentGun()->getCoordinate());
                }
            }
        }else if(state == 2){
            move(dir.x,dir.y);
            Boss::setDmgHit(Boss::getInitialDmg() * 1.5);
            delay->start();
            if(onDelay == false){
                Coordinate aux = Enemy::getTrigonometry()->direction(*rath->getCoordinate(), *Entity::getCoordinate());
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
        }else if(state == 3){
            if(guns.size() > 1 && currentGun != 1){
                currentGun = 1;
                changeGun(currentGun);
            }
            Entity::setSpeed(Boss::getInitialSpeed() * 0.5);
            move(dir.x,dir.y);
            if(!Boss::getHitbox()->checkCollision(rath->getHitbox())){
                Boss::gunAttack();
                Boss::getCurrentGun()->getBullet()->setPosition(*Boss::getCurrentGun()->getCoordinate());
                angle += 15;
            }        
        }else if(state == 4){
            Entity::setSpeed(Enemy::getInitialSpeed() * 1.5);
            move(dir.x,dir.y);
            Enemy::setDmgHit(Enemy::getInitialDmg() * 1.5);
        }else if(state == 5){
            Entity::setSpeed(Boss::getInitialSpeed() * 0.8);
            move(dir.x,dir.y);
            if(getCurrentGun()->getBulletLifetime()->isExpired()){
                srand (time(NULL));
                int num = rand() % 2;
                if(num == 0 && guns.at(1)->getGunCooldown()->isExpired()){
                    currentGun = 1;
                    changeGun(currentGun);
                }else if(num == 1 && guns.at(0)->getGunCooldown()->isExpired()){
                    currentGun = 0;
                    changeGun(currentGun);
                }
            }
            if(getCurrentGun()->getGunCooldown()->isExpired()){
            //changeGun(0);
                Boss::gunAttack();
                Boss::getCurrentGun()->getBullet()->setPosition(*Boss::getCurrentGun()->getCoordinate());
            }
            if(currentGun == 1){
                angle += 15;
            }
            if(rath->getFlashCooldown()->isRunning() && getFlashCooldown()->isExpired()){
                flash(dir.x,dir.y);
            }
        }
    }else{
        state = 0;
    }
    
    
    
}
