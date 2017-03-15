#include "HUD.h"

    HUD::HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC){
        background = bg;
        guns = gs;
        gunsOff = gsO;
        playerHP = pHP;
        bossHP = bHP;
        flashCooldown = fC;
        
        activeGun = 0;
    }
    
    HUD::~HUD(){

    }

    void HUD::changeActiveGun(int gun){
        activeGun = gun;
    }
    
    void HUD::changePlayerLife(int life){

    }
    
    void HUD::activeBossLife(int life){

    }
    
    void HUD::changeBossLife(int life){

    }
    
    void HUD::changeFlashCooldown(){

    }

    bool HUD::drawHUD(sf::RenderWindow* window, int maxLife, int life, int maxLifeBoss, int lifeBoss){
        window->draw(background->getSprite());
        drawGun(window);
        drawPlayerHP(window, maxLife, life);
        drawBossHP(window, maxLifeBoss, lifeBoss);
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
    void HUD::drawPlayerHP(sf::RenderWindow *window, int maxLife, int life){
        int newW = (life*playerHP->getW())/maxLife;
        if(newW < playerHP->getW() && newW >= 0){
            playerHP->setSize(newW, playerHP->getH());
            window->draw(playerHP->getSprite());
        }else {
            playerHP->setSize(playerHP->getW(), playerHP->getH());
            window->draw(playerHP->getSprite());
        }
    }
    void HUD::drawBossHP(sf::RenderWindow *window, int maxLifeBoss, int lifeBoss){
        int newW = (lifeBoss*bossHP->getW())/maxLifeBoss;
        if(newW < bossHP->getW() && newW >= 0){
            bossHP->setSize(newW, bossHP->getH());
            window->draw(bossHP->getSprite());
        }else {
            bossHP->setSize(bossHP->getW(), bossHP->getH());
            window->draw(bossHP->getSprite());
        }
    }