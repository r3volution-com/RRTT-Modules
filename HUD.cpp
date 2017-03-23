#include <sstream>

#include "HUD.h"
#include "Coordinate.h"
#include "Button.h"

HUD::HUD(Sprite *bg, Sprite *hd, Sprite *pHP, Sprite *bHP, Font *f){
    background = bg;
    hud = hd;
    playerHP = pHP;
    bossHP = bHP;
    
    clockFlash = new sf::Clock;
    clockFirstGun = new sf::Clock;
    clockSecondGun = new sf::Clock;
    
    timeFlash = 4.0f;
    firstGunCooldown = 5.0f;
    secondGunCooldown = 2.0f;
    
    font = f;
    lifePlayerText = new Text(std::string(), 0, 0, font, false);
    sf::Color color = sf::Color::Black;
    lifePlayerText->setStyles(color, color, 0, 12);

    
    firstGunUsed = false;
    secondGunUsed = false;
    flashUsed = false;
    
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
    /*int newW = (lifePlayer*playerHP->getMaxW())/maxLifePlayer;
    if(newW < playerHP->getMaxW() && newW >= 0){
        playerHP->setSize(newW, playerHP->getMaxH());
    }*/
}

void HUD::changeMaxLifeBoss(int maxLife){
    maxLifeBoss = maxLife;
}

void HUD::changeLifeBoss(int life){
    lifeBoss = life;
    /*int newW = (lifeBoss*bossHP->getMaxW())/maxLifeBoss;
    if(newW < bossHP->getMaxW() && newW >= 0){
        bossHP->setSize(newW, bossHP->getMaxH());
    }*/
}

void HUD::changeFlashCooldown(int cooldown){
    timeFlash = cooldown;
}

void HUD::changeFirstGunCooldown(int cooldown){
    firstGunCooldown = cooldown;
}

void HUD::changeSecondGunCooldown(int cooldown){
    secondGunCooldown = cooldown;
}

void HUD::setSpriteGunsOn(std::vector<Sprite*>* gs){
    guns = gs;
}

void HUD::setSpriteGunsOff(std::vector<Sprite*>* gsO){
    gunsOff = gsO;
}

void HUD::setSpriteGunsCooldown(std::vector<Sprite*>* gCd){
    gunsCooldown = gCd;
    for (int i = 0; i<gCd->size(); i++){
        gunsCooldown->at(i)->setSize(0,0);
    }
}

void HUD::setSpriteFlash(Sprite* fC){
    flash = fC;
}

void HUD::setSpriteFlashCooldown(Sprite* cool){
    flashCooldown = cool;
}

void HUD::setTextLayer(float x, float y, Sprite *sp){
    textSprite = sp;
    //textSprite->setPosition(x, y);
    currentText = new Text(std::string(), 0, 0, font, false);
    talker = new Text(std::string(), 0, 0, font, false);
}

void HUD::setTLayerTalker(std::string s, float x, float y){
    talker->setText(s);
    talker->setPosition(x, y);
}

void HUD::setTLayerText(std::string s, float x, float y){
    currentText->setText(s);
    currentText->setPosition(x, y);
}

void HUD::setTLayerTextParams(int size, sf::Color fillColor, sf::Color outlineColor){
    currentText->setStyles(fillColor, outlineColor, 1, size);
}

void HUD::setTextLifePlayer(){
    std::stringstream life;
    life << lifePlayer << "/" << maxLifePlayer;
    lifePlayerText->setText(life.str());
    float x = playerHP->getPosition().x ;
    float y = playerHP->getPosition().y;
    lifePlayerText->setPosition(x, y);
}

bool HUD::drawHUD(sf::RenderWindow* window){
    window->draw(background->getSprite());
    window->draw(hud->getSprite());
    drawGun(window);
    drawPlayerHP(window);
    drawBossHP(window);
    drawFlash(window);
    window->draw(*lifePlayerText->getText());
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
    if(clockFlash->getElapsedTime().asSeconds() < timeFlash){
        //flashCooldown->setSize(flashCooldown->getW()-(flashCooldown->getMaxW()/(120.0f*timeFlash)), flashCooldown->getH());  //ToDo mirar fps para un numero menor en caso del pc ir mas lento
    } else flashUsed = false;
    if (flashUsed) window->draw(flashCooldown->getSprite());
}
void HUD::drawGunCooldown(sf::RenderWindow* window){
    if(clockFirstGun->getElapsedTime().asSeconds() < firstGunCooldown){
        //gunsCooldown->at(0)->setSize(gunsCooldown->at(0)->getW()-(gunsCooldown->at(0)->getMaxW()/(120.0f*firstGunCooldown)), gunsCooldown->at(0)->getH());  //ToDo mirar fps para un numero menor en caso del pc ir mas lento  
    } else firstGunUsed = false;
    
    if(clockSecondGun->getElapsedTime().asSeconds() < secondGunCooldown){
        //gunsCooldown->at(1)->setSize(gunsCooldown->at(1)->getW()-(gunsCooldown->at(1)->getMaxW()/(120.0f*secondGunCooldown)), gunsCooldown->at(1)->getH());  //ToDo mirar fps para un numero menor en caso del pc ir mas lento
    } else secondGunUsed = false;
    
    if(activeGun == 0 && firstGunUsed) window->draw(gunsCooldown->at(0)->getSprite());
    else if(activeGun == 1 && secondGunUsed) window->draw(gunsCooldown->at(1)->getSprite());
}

void HUD::drawTextLayer(sf::RenderWindow *window){
    window->draw(textSprite->getSprite());
    window->draw(*talker->getText());
    window->draw(*currentText->getText());
}

void HUD::resetClockFlash(){
    if (!flashUsed){
        clockFlash->restart();
        flashCooldown->restoreSize();
        flashUsed = true;
    }
}

void HUD::resetClock(){
    if(activeGun == 0){
        if (!firstGunUsed) {
            clockFirstGun->restart();
            firstGunUsed = true;
            gunsCooldown->at(activeGun)->restoreSize();
        }
    }else if(activeGun == 1){
        if (!secondGunUsed){
            clockSecondGun->restart();
            secondGunUsed = true;
            gunsCooldown->at(activeGun)->restoreSize();
        }
    }
}

void HUD::resetStats(){
    lifePlayer = maxLifePlayer;
    lifeBoss = maxLifeBoss;

    clockFlash->restart();
    flashCooldown->restoreSize();
    flashUsed = true;

    clockFirstGun->restart();
    firstGunUsed = true;
    gunsCooldown->at(0)->restoreSize();

    clockSecondGun->restart();
    secondGunUsed = true;
    gunsCooldown->at(1)->restoreSize();
}

void HUD::setSpriteDie(Sprite* sd){
    die = sd;
}

void HUD::setButton(Coordinate *coor, Texture* tex, Rect *rect){
    buttonDie = new Button(coor, tex, rect);
}

void HUD::drawDie(sf::RenderWindow *window){
    if(lifePlayer == 0){
        window->draw(die->getSprite());
        buttonDie->draw(window);
        if(buttonDie->getHover() == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            resetStats();
        }
    }
}
