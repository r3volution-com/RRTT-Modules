#include "HUD.h"

HUD::HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC, Sprite *fCO){
    background = bg;
    guns = gs;
    gunsOff = gsO;
    playerHP = pHP;
    bossHP = bHP;
    flash = fC;
    flashCooldown = fCO;
    
    clock = new sf::Clock;
    
    timeFlash = 1.5f;
    firstGunCooldown = 4.0f;
    secondGunCooldown = 2.0f;
    activeGun = 0;
    maxLifeBoss = 150;
    lifeBoss = 150;
    maxLifePlayer = 100;
    lifePlayer = 100;
    
}

HUD::~HUD(){

}

void HUD::changeActiveGun(int gun){
    activeGun = gun;
}

void HUD::changeMaxLifePlayer(int maxLife){
    maxLifePlayer = maxLife;
}

void HUD::changeLifePlayer(int life){
    lifePlayer = life;
    int newW = (lifePlayer*playerHP->getMaxW())/maxLifePlayer;
    if(newW < playerHP->getMaxW() && newW >= 0){
        playerHP->setSize(newW, playerHP->getMaxH());
    }
}

void HUD::changeMaxLifeBoss(int maxLife){
    maxLifeBoss = maxLife;
}

void HUD::changeLifeBoss(int life){
    lifeBoss = life;
    int newW = (lifeBoss*bossHP->getMaxW())/maxLifeBoss;
    if(newW < bossHP->getMaxW() && newW >= 0){
        bossHP->setSize(newW, bossHP->getMaxH());
    }
}

void HUD::changeFlashCooldown(int cooldown){
    flashCooldown = cooldown;
}

void HUD::changeFirstGunCooldown(int cooldown){
    firstGunCooldown = cooldown;
}

void HUD::changeSecondGunCooldown(int cooldown){
    secondGunCooldown = cooldown;
}

bool HUD::drawHUD(sf::RenderWindow* window){
    window->draw(background->getSprite());
    drawGun(window);
    drawPlayerHP(window);
    drawBossHP(window);
    drawFlash(window);
}

void HUD::drawGun(sf::RenderWindow *window){
    if(activeGun == 0){
        window->draw(guns->at(0)->getSprite());
        window->draw(gunsOff->at(1)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }else if(activeGun == 1){
        window->draw(guns->at(1)->getSprite());
        window->draw(gunsOff->at(0)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }/*else if(activeGun == 2){
        window->draw(guns->at(2)->getSprite());
        window->draw(gunsOff->at(0)->getSprite());
        window->draw(gunsOff->at(1)->getSprite());

    }*/
}

void HUD::drawPlayerHP(sf::RenderWindow *window){
    window->draw(playerHP->getSprite());
}

void HUD::drawBossHP(sf::RenderWindow *window){
    window->draw(bossHP->getSprite());
}

void HUD::drawFlash(sf::RenderWindow* window){
    window->draw(flash->getSprite());
}

void HUD::drawFlashCooldown(sf::RenderWindow *window){
    if(clock->getElapsedTime().asSeconds() < timeFlash){
        window->draw(flashCooldown->getSprite());
        flashCooldown->setSize(flashCooldown->getW()-(timeFlash/120.0f), flashCooldown->getH());  //ToDo mirar fps para un numero menor en caso del pc ir mas lento
        return true;
    }
    flashCooldown->restoreSize();
    return false;
}

void HUD::resetClock(){
    clock->restart();
}