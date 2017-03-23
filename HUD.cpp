#include <sstream>

#include "HUD.h"
#include "Coordinate.h"
#include "Button.h"

HUD::HUD(Texture *tex, Texture *tex2, Texture *tex3, Texture *tex4, Font *f){
    
    Rect *rectBack = new Rect(0, 0, 1280, 720);
    background = new Sprite(tex, rectBack);
    hud = new Sprite(tex2, rectBack);
    die = new Sprite(tex3, rectBack);
    Rect *rectLife = new Rect(0, 0, 194, 14);
    playerHP = new Sprite(tex4, rectLife);
    playerHP->move(300.0f,30.0f);
    bossHP = new Sprite(tex4,rectLife);
    bossHP->move(590.0f,680.0f);
    
    guns = new std::vector<Sprite*>();
    gunsOff = new std::vector<Sprite*>();
    gunsCooldown = new std::vector<Sprite*>();
    
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
    int newW = (lifePlayer*playerHP->getOriginalSpriteRect()->w)/maxLifePlayer;
    if(newW < playerHP->getOriginalSpriteRect()->w && newW >= 0){
        playerHP->setSize(newW, playerHP->getOriginalSpriteRect()->h);
    }
}

void HUD::changeMaxLifeBoss(int maxLife){
    maxLifeBoss = maxLife;
}

void HUD::changeLifeBoss(int life){
    lifeBoss = life;
    int newW = (lifeBoss*bossHP->getOriginalSpriteRect()->w)/maxLifeBoss;
    if(newW < bossHP->getOriginalSpriteRect()->w && newW >= 0){
        bossHP->setSize(newW, bossHP->getOriginalSpriteRect()->h);
    }
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

void HUD::setSpriteGunsOn(Texture *tex, Texture *tex2){
    Rect *rectGun = new Rect(0, 0, 80, 80);
    Sprite *gun1 = new Sprite(tex, rectGun);
    gun1->move(17.0f,18.0f);
    Sprite *gun2 = new Sprite(tex2, rectGun);
    gun2->move(17.0f,98.0f);
    
    guns->push_back(gun1);
    guns->push_back(gun2);
    
}

void HUD::setSpriteGunsOff(Texture *tex, Texture *tex2){
    Rect *rectGun = new Rect(0, 0, 80, 80);
    Sprite *go1 = new Sprite(tex, rectGun);
    go1->move(17.0f,18.0f);
    Sprite *go2 = new Sprite(tex2, rectGun);
    go2->move(17.0f,98.0f);
    
    gunsOff->push_back(go1);
    gunsOff->push_back(go2);
}

void HUD::setSpriteGunsCooldown(Texture *tex){
    Rect *rectGun = new Rect(0, 0, 80, 80);
    Sprite *gc1 = new Sprite(tex, rectGun);
    gc1->move(17.0f,18.0f);
    Sprite *gc2 = new Sprite(tex, rectGun);
    gc2->move(17.0f,98.0f);
    
    gunsCooldown->push_back(gc1);
    gunsCooldown->push_back(gc2);
    
    for (int i = 0; i<gunsCooldown->size(); i++){
        gunsCooldown->at(i)->setSize(0,0);
        std::cout<< gunsCooldown->at(i)->getOriginalSpriteRect();
    }
}

void HUD::setSpriteFlash(Texture *tex){
    Rect *rectFlash = new Rect(0, 0, 80, 80);
    flash = new Sprite(tex,rectFlash);
    flash->move(100.0f,18.0f);
}

void HUD::setSpriteFlashCooldown(Texture *tex){
    Rect *rectFlash = new Rect(0, 0, 80, 80);
    flashCooldown = new Sprite(tex, rectFlash);
    flashCooldown->move(100.0f,18.0f);
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
   /* drawGun(window);
    drawPlayerHP(window);
    drawBossHP(window);
    drawFlash(window);
    window->draw(*lifePlayerText->getText());*/
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
        flashCooldown->setSize(flashCooldown->getActualSpriteRect()->w-(flashCooldown->getOriginalSpriteRect()->w/(120.0f*timeFlash)), flashCooldown->getActualSpriteRect()->h);  //ToDo mirar fps para un numero menor en caso del pc ir mas lento
    } else flashUsed = false;
    if (flashUsed) window->draw(flashCooldown->getSprite());
}
void HUD::drawGunCooldown(sf::RenderWindow* window){
    if(clockFirstGun->getElapsedTime().asSeconds() < firstGunCooldown){
        std::cout<<gunsCooldown->at(0)->getActualSpriteRect()->w << "-" << gunsCooldown->at(0)->getOriginalSpriteRect()->w << "/" << 120.0f*firstGunCooldown<<"\n";
        gunsCooldown->at(0)->setSize(gunsCooldown->at(0)->getActualSpriteRect()->w-(gunsCooldown->at(0)->getOriginalSpriteRect()->w/(120.0f*firstGunCooldown)), gunsCooldown->at(0)->getActualSpriteRect()->h);  //ToDo mirar fps para un numero menor en caso del pc ir mas lento  
    } else firstGunUsed = false;
    
    if(clockSecondGun->getElapsedTime().asSeconds() < secondGunCooldown){
        gunsCooldown->at(1)->setSize(gunsCooldown->at(1)->getActualSpriteRect()->w-(gunsCooldown->at(1)->getOriginalSpriteRect()->w/(120.0f*secondGunCooldown)), gunsCooldown->at(1)->getActualSpriteRect()->h);  //ToDo mirar fps para un numero menor en caso del pc ir mas lento
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

void HUD::setButton(Coordinate *coor, Texture* tex, Rect *rect){
    buttonDie = new Button(coor, tex, rect);
}

bool HUD::drawDie(sf::RenderWindow *window){
    std::cout<<lifePlayer<<"\n";
    if(lifePlayer <= 0){
        window->draw(die->getSprite());
        buttonDie->setText("Has Muerto", sf::Color::White, sf::Color::Black, font, 12);
        buttonDie->draw(window);
        if(buttonDie->getHover() == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            resetStats();
            return true;
        }
    }
    return false;
}
