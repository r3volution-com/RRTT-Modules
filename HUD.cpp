#include "HUD.h"
#include "Game.h"

HUD::HUD(Texture *hTex, Texture *lTex, Rect<float> lRect, Font *f, Time *cF){
    
    tex = lTex;
    
    hud = new Sprite(hTex, Rect<float>(0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    playerHP = new Sprite(tex, lRect);
    playerHP->setPosition(296.5f,30.0f);
    
    
    guns = new std::vector<Sprite*>();
    gunsOff = new std::vector<Sprite*>();
    gunsCooldown = new std::vector<Sprite*>();
    
    clockFlash = new Time();
    clockFirstGun = new Time();
    clockSecondGun = new Time();
    
    firstGunCooldown = 5.0f;
    secondGunCooldown = 2.0f;
    
    font = f;
    lifePlayerText = new Text(std::string(), Coordinate(0,0), font, false);
    sf::Color color = sf::Color::Black;
    lifePlayerText->setStyles(color, color, 0, 12);
    
    activeGun = 0;
    maxLifeBoss = 100;
    lifeBoss = 100;
    maxLifePlayer = 100;
    lifePlayer = 100;
    
    dieBool = false;
    
    flashModuleEnabled = false;
    gunsModuleEnabled = false;
    dieModuleEnabled = false;
    textModuleEnabled = false;
    bossModuleEnable = false;
    
}

HUD::~HUD(){
    delete hud;
    delete guns;
    delete gunsOff;
    delete gunsCooldown;
    delete playerHP;
    delete bossHP;
    delete flash;
    delete flashCooldown;
    delete die;

    delete clockFlash; 
    delete clockFirstGun; 
    delete clockSecondGun; 

    delete textSprite;
    delete talker;
    delete currentText;

    delete lifePlayerText;

    delete buttonDie;
    
    hud = NULL;
    guns = NULL;
    gunsOff = NULL;
    gunsCooldown = NULL;
    playerHP = NULL;
    bossHP = NULL;
    flash = NULL;
    flashCooldown = NULL;
    die = NULL;

    clockFlash = NULL; 
    clockFirstGun = NULL; 
    clockSecondGun = NULL; 

    textSprite = NULL;
    talker = NULL;
    currentText = NULL;

    lifePlayerText = NULL;

    buttonDie = NULL;
    
}

void HUD::setGuns(Rect<float> rect, Time *g1, Time *g2){    
    guns->push_back(new Sprite(tex, Rect<float>(rect.x, rect.y, rect.w, rect.h)));
    guns->at(0)->setPosition(17.0f,18.0f);
    guns->push_back(new Sprite(tex, Rect<float>(rect.x+80, rect.y, rect.w, rect.h)));
    guns->at(1)->setPosition(17.0f,98.0f);
    
    gunsOff->push_back(new Sprite(tex, Rect<float>(rect.x+160, rect.y, rect.w, rect.h)));
    gunsOff->at(0)->setPosition(17.0f,18.0f);
    gunsOff->push_back(new Sprite(tex, Rect<float>(rect.x+240, rect.y, rect.w, rect.h)));
    gunsOff->at(1)->setPosition(17.0f,98.0f);
    gunsModuleEnabled = true;
    
    gunsCooldown->push_back(new Sprite(tex, Rect<float>(rect.x+320, rect.y, rect.w, rect.h)));
    gunsCooldown->at(0)->setPosition(17.0f,18.0f);
    gunsCooldown->push_back(new Sprite(tex, Rect<float>(rect.x+400, rect.y, rect.w, rect.h)));
    gunsCooldown->at(1)->setPosition(17.0f,98.0f);
    
    for (int i = 0; i<gunsCooldown->size(); i++){
        gunsCooldown->at(i)->setSize(0,0);
    }
    //ToDo PabloL: MIRAR PARA HACERLO MODULAR (VECTOR)
    clockFirstGun = g1;
    clockSecondGun = g2;
    
    firstGunCooldown = g1->getTime();
    secondGunCooldown = g2->getTime();
}

void HUD::setFlash(Rect<float> rect, Time *f){
    flash = new Sprite(tex, Rect<float>(rect.x, rect.y+80, rect.w, rect.h));
    flash->setPosition(100.0f,18.0f);
    flashCooldown = new Sprite(tex, Rect<float>(rect.x+80, rect.y+80, rect.w, rect.h));
    flashCooldown->setPosition(100.0f,18.0f);
    flashModuleEnabled = true;
    clockFlash = f;
    timeFlash = f->getTime(); 
}

void HUD::setDieSprite(Texture *dTex){
    die = new Sprite(dTex, Rect<float> (0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    dieModuleEnabled = true;
}

void HUD::setBossLife(Rect<float> tRect){
    bossHP = new Sprite(tex, tRect);
    bossHP->setPosition(528.0f,667.0f); 
    bossModuleEnable = true;
}

void HUD::setTextLayer(Coordinate coord, Rect<float> tRect, Texture *tTex){
    textSprite = new Sprite(tTex, tRect);
    textSprite->setPosition(coord);
    currentText = new Text(std::string(), Coordinate(0,0), font, false);
    talker = new Text(std::string(), Coordinate(0,0), font, false);
    textModuleEnabled = true;
}

void HUD::setTLayerTalker(std::string s, float x, float y){
    talker->setText(s);
    talker->setPosition(Coordinate(x, y));
}

void HUD::setTLayerText(std::string s, float x, float y){
    currentText->setText(s);
    currentText->setPosition(Coordinate(x, y));
}

void HUD::setTLayerTextParams(int size, sf::Color fillColor, sf::Color outlineColor){
    currentText->setStyles(fillColor, outlineColor, 1, size);
}

void HUD::setTextLifePlayer(){
    std::stringstream life;
    life << lifePlayer << "/" << maxLifePlayer;
    lifePlayerText->setText(life.str());
    float x = playerHP->getPosition().x + 2*(playerHP->getOriginalSpriteRect()->w/5);
    float y = playerHP->getPosition().y;
    lifePlayerText->setPosition(Coordinate(x, y));
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
    if(newW <= playerHP->getOriginalSpriteRect()->w && newW >= 0){
        playerHP->setSize(newW, playerHP->getOriginalSpriteRect()->h);
    }
}

void HUD::changeMaxLifeBoss(int maxLife){
    maxLifeBoss = maxLife;
}

void HUD::changeLifeBoss(int life){
    lifeBoss = life;
    int newW = (lifeBoss*bossHP->getOriginalSpriteRect()->w)/maxLifeBoss;
    if(newW <= bossHP->getOriginalSpriteRect()->w && newW >= 0){
        bossHP->setSize(newW, bossHP->getOriginalSpriteRect()->h);
    }
}

bool HUD::drawHUD(){
    Game::Instance()->window->draw(*hud->getSprite());
    drawPlayerHP();
    Game::Instance()->window->draw(*lifePlayerText->getText());
    if (bossModuleEnable) drawBossHP(); 
    if (gunsModuleEnabled) drawGun();
    if (flashModuleEnabled) drawFlash();
}

void HUD::drawGun(){
    if(activeGun == 0){
        Game::Instance()->window->draw(*guns->at(0)->getSprite());
        Game::Instance()->window->draw(*gunsOff->at(1)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }else if(activeGun == 1){
        Game::Instance()->window->draw(*guns->at(1)->getSprite());
        Game::Instance()->window->draw(*gunsOff->at(0)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }/*else if(activeGun == 2){
        window->draw(guns->at(2)->getSprite());
        window->draw(gunsOff->at(0)->getSprite());
        window->draw(gunsOff->at(1)->getSprite());

    }*/
}

void HUD::drawPlayerHP(){
    Game::Instance()->window->draw(*playerHP->getSprite());
}

void HUD::drawBossHP(){
    Game::Instance()->window->draw(*bossHP->getSprite());
}

void HUD::drawFlash(){
    Game::Instance()->window->draw(*flash->getSprite());
}

void HUD::drawFlashCooldown(){
    if(clockFlash->getTime() < timeFlash){
        flashCooldown->setSize(flashCooldown->getActualSpriteRect()->w-(flashCooldown->getOriginalSpriteRect()->w/(Game::Instance()->fps*timeFlash)), flashCooldown->getActualSpriteRect()->h);
    } else {
        clockFlash->pause();
    }
    if (clockFlash->isRunning()) Game::Instance()->window->draw(*flashCooldown->getSprite());
}
void HUD::drawGunCooldown(){
    if(clockFirstGun->getTime() < firstGunCooldown){
        gunsCooldown->at(0)->setSize(gunsCooldown->at(0)->getActualSpriteRect()->w-(gunsCooldown->at(0)->getOriginalSpriteRect()->w/(Game::Instance()->fps*firstGunCooldown)), 
                gunsCooldown->at(0)->getActualSpriteRect()->h);
    } else {
       clockFirstGun->pause();
    }
    
    if(clockSecondGun->getTime() < secondGunCooldown){
        gunsCooldown->at(1)->setSize(gunsCooldown->at(1)->getActualSpriteRect()->w-(gunsCooldown->at(1)->getOriginalSpriteRect()->w/(Game::Instance()->fps*secondGunCooldown)), 
                gunsCooldown->at(1)->getActualSpriteRect()->h);
    } else {
        clockSecondGun->pause();
    }
    
    if(activeGun == 0 && clockFirstGun->isRunning()) Game::Instance()->window->draw(*gunsCooldown->at(0)->getSprite());
    else if(activeGun == 1 && clockSecondGun->isRunning()) Game::Instance()->window->draw(*gunsCooldown->at(1)->getSprite());
}

void HUD::drawTextLayer(){
    Game::Instance()->window->draw(*textSprite->getSprite());
    Game::Instance()->window->draw(*talker->getText());
    Game::Instance()->window->draw(*currentText->getText());
}

void HUD::resetClockFlash(){
    if (clockFlash->getTime() == 0){ 
        flashCooldown->restoreSize();
    }
}

void HUD::resetClock(){ 
    if(activeGun == 0){
        if (clockFirstGun->getTime() == 0) {
            gunsCooldown->at(activeGun)->restoreSize();
        }
    }else if(activeGun == 1){
        if (clockSecondGun->getTime() == 0){
            gunsCooldown->at(activeGun)->restoreSize();
        }
    }
}

void HUD::resetStats(){
    changeLifePlayer(maxLifePlayer);
    changeLifeBoss(maxLifeBoss);
    
    playerHP->restoreSize();
    bossHP->restoreSize();
    
    dieBool = false;
}

void HUD::setButton(Coordinate coor, Texture* tex, Rect<float> rect){
    buttonDie = new Button(coor, tex, rect);
}

void HUD::drawDie(){
    if(lifePlayer <= 0){
        Game::Instance()->window->draw(*die->getSprite());
        buttonDie->draw();
    }
    
}

bool HUD::checkDie(){
    if(lifePlayer <= 0){
        if(dieBool == false){
            sf::sleep(sf::seconds(2));
            dieBool = true;
        }
        buttonDie->setText("Has Muerto", sf::Color::White, sf::Color::Black, font, 12);
        return true;
    }
    return false;
}
