#include "HUD.h"
#include "Game.h"

HUD::HUD(Texture *bTex, Texture *hTex, Texture *lTex, Font *f, Time *cF){
    
    background = new Sprite(bTex, Rect<float>(0, 0, 1280, 720));
    hud = new Sprite(hTex, Rect<float>(0, 0, 1280, 720));
    playerHP = new Sprite(lTex, Rect<float>(100, 230, 194, 14));
    playerHP->setPosition(296.5f,30.0f);
    bossHP = new Sprite(lTex, Rect<float>(100, 230, 194, 14));
    bossHP->setPosition(528.0f,667.0f);
    
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

    firstGunUsed = false;
    secondGunUsed = false;
    flashUsed = false;
    
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
    
    window = game->window;
}

HUD::~HUD(){
    delete background;
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
    
    
    background = NULL;
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

void HUD::setSpriteGuns(Texture* tex){    
    guns->push_back(new Sprite(tex, Rect<float>(10, 10, 80, 80)));
    guns->at(0)->setPosition(17.0f,18.0f);
    guns->push_back(new Sprite(tex, Rect<float>(100, 10, 80, 80)));
    guns->at(1)->setPosition(17.0f,98.0f);
    
    gunsOff->push_back(new Sprite(tex, Rect<float>(10, 190, 80, 80)));
    gunsOff->at(0)->setPosition(17.0f,18.0f);
    gunsOff->push_back(new Sprite(tex, Rect<float>(100, 140, 80, 80)));
    gunsOff->at(1)->setPosition(17.0f,98.0f);
    gunsModuleEnabled = true;
    
    gunsCooldown->push_back(new Sprite(tex, Rect<float>(190, 10, 80, 80)));
    gunsCooldown->at(0)->setPosition(17.0f,18.0f);
    gunsCooldown->push_back(new Sprite(tex, Rect<float>(190, 10, 80, 80)));
    gunsCooldown->at(1)->setPosition(17.0f,98.0f);
    
    for (int i = 0; i<gunsCooldown->size(); i++){
        gunsCooldown->at(i)->setSize(0,0);
    }
}

void HUD::setFlash(Texture *tFlash, Texture *tCooldown, Time *f){
    flash = new Sprite(tFlash, Rect<float>(10, 100, 80, 80));
    flash->setPosition(100.0f,18.0f);
    flashCooldown = new Sprite(tCooldown, Rect<float>(190, 10, 80, 80));
    flashCooldown->setPosition(100.0f,18.0f);
    flashModuleEnabled = true;
    clockFlash = f;
    timeFlash = f->getTime(); //ToDo PabloL: Para llenar el float y saber el tiempo siempre
}

void HUD::setDieSprite(Texture *dTex){
    die = new Sprite(dTex, Rect<float>(0, 0, 1280, 720));
    dieModuleEnabled = true;
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

void HUD::changeFirstGunCooldown(int cooldown){
    firstGunCooldown = cooldown;
}

void HUD::changeSecondGunCooldown(int cooldown){
    secondGunCooldown = cooldown;
}

bool HUD::drawHUD(){
    window->draw(*background->getSprite());
    window->draw(*hud->getSprite());
    drawPlayerHP(window);
    window->draw(*lifePlayerText->getText());
    drawBossHP(window);
    if (gunsModuleEnabled) drawGun(window);
    if (flashModuleEnabled) drawFlash(window);
}

void HUD::drawGun(){
    if(activeGun == 0){
        window->draw(*guns->at(0)->getSprite());
        window->draw(*gunsOff->at(1)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }else if(activeGun == 1){
        window->draw(*guns->at(1)->getSprite());
        window->draw(*gunsOff->at(0)->getSprite());
        //window->draw(gunsOff->at(2)->getSprite());
    }/*else if(activeGun == 2){
        window->draw(guns->at(2)->getSprite());
        window->draw(gunsOff->at(0)->getSprite());
        window->draw(gunsOff->at(1)->getSprite());

    }*/
}

void HUD::drawPlayerHP(){
    window->draw(*playerHP->getSprite());
}

void HUD::drawBossHP(){
    window->draw(*bossHP->getSprite());
}

void HUD::drawFlash(){
    window->draw(*flash->getSprite());
}

void HUD::drawFlashCooldown(){
    if(clockFlash->getTime() < timeFlash){
        flashCooldown->setSize(flashCooldown->getActualSpriteRect()->w-(flashCooldown->getOriginalSpriteRect()->w/(Game::Instance()->fps*timeFlash)), flashCooldown->getActualSpriteRect()->h);
    } else flashUsed = false;
    if (flashUsed) window->draw(*flashCooldown->getSprite());
}
void HUD::drawGunCooldown(){
    if(clockFirstGun->getTime() < firstGunCooldown){
        gunsCooldown->at(0)->setSize(gunsCooldown->at(0)->getActualSpriteRect()->w-(gunsCooldown->at(0)->getOriginalSpriteRect()->w/(Game::Instance()->fps*firstGunCooldown)), gunsCooldown->at(0)->getActualSpriteRect()->h);
    } else firstGunUsed = false;
    
    if(clockSecondGun->getTime() < secondGunCooldown){
        gunsCooldown->at(1)->setSize(gunsCooldown->at(1)->getActualSpriteRect()->w-(gunsCooldown->at(1)->getOriginalSpriteRect()->w/(Game::Instance()->fps*secondGunCooldown)), gunsCooldown->at(1)->getActualSpriteRect()->h);
    } else secondGunUsed = false;
    
    if(activeGun == 0 && firstGunUsed) window->draw(*gunsCooldown->at(0)->getSprite());
    else if(activeGun == 1 && secondGunUsed) window->draw(*gunsCooldown->at(1)->getSprite());
}

void HUD::drawTextLayer(){
    window->draw(*textSprite->getSprite());
    window->draw(*talker->getText());
    window->draw(*currentText->getText());
}

void HUD::resetClockFlash(){
    if (clockFlash->getTime() >= timeFlash){ //ToDo PabloL: Hecho -> mirar si esta bien usado el get
        flashCooldown->restoreSize();
        
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
    changeLifePlayer(maxLifePlayer);
    changeLifeBoss(maxLifeBoss);
    
    playerHP->restoreSize();
    bossHP->restoreSize();
    
    /*clockFlash->restart();
    flashCooldown->restoreSize();
    flashUsed = true;

    clockFirstGun->restart();
    firstGunUsed = true;
    gunsCooldown->at(0)->restoreSize();

    clockSecondGun->restart();
    secondGunUsed = true;
    gunsCooldown->at(1)->restoreSize();*/
    
    dieBool = false;
}

void HUD::setButton(Coordinate coor, Texture* tex, Rect<float> rect){
    buttonDie = new Button(coor, tex, rect);
}

void HUD::drawDie(){
    if(lifePlayer <= 0){
        window->draw(*die->getSprite());
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
