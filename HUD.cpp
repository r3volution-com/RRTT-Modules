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

    bool HUD::drawHUD(sf::RenderWindow* window){
        window->draw(background->getSprite());
        drawGun(window);
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
    }