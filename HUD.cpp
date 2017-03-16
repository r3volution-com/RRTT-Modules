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
    activeGun = 0;
    maxLifeBoss = 150;
    lifeBoss = 150;
    maxLife = 100;
    life = 100;
    
}

HUD::~HUD(){

}

void HUD::changeActiveGun(int gun){
    activeGun = gun;
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
    int newW = (life*playerHP->getW())/maxLife;
    if(newW < playerHP->getW() && newW >= 0){
        playerHP->setSize(newW, playerHP->getH());
        window->draw(playerHP->getSprite());
    }else {
        playerHP->restoreSize();
        window->draw(playerHP->getSprite());
    }
}
void HUD::drawBossHP(sf::RenderWindow *window){
    int newW = (lifeBoss*bossHP->getW())/maxLifeBoss;
    if(newW < bossHP->getW() && newW >= 0){
        bossHP->setSize(newW, bossHP->getH());
        window->draw(bossHP->getSprite());
    }else {
        bossHP->restoreSize();
        window->draw(bossHP->getSprite());
    }
}
void HUD::drawFlash(sf::RenderWindow* window){
    window->draw(flash->getSprite());
}
bool HUD::drawFlashCooldown(sf::RenderWindow *window){
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