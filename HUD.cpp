#include "HUD.h"
#include "Game.h"

HUD::HUD(Texture *hTex, Texture *rTex, Rect<float> lRect, Rect<float> cdRect, Font *f){
    hud = new Sprite(hTex, Rect<float>(0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    
    tex = rTex;
    font = f;
    
    cooldownRect = new Rect<float> (cdRect);
    
    //ToDo: la vida deberia ser modular
    playerHP = new Sprite(tex, lRect); 
    playerHP->setPosition(296.5f,30.0f);
    lifePlayerText = new Text(std::string(), Coordinate(0,0), font, false);
    lifePlayerText->setStyles(sf::Color::Black, sf::Color::Black, 0, 12);
    maxLifePlayer = 100;
    lifePlayer = maxLifePlayer;
    //Fin
    
    guns = new std::vector<Sprite*>();
    gunsOff = new std::vector<Sprite*>();
    gunsCooldown = new std::vector<Sprite*>();
    gunTimers = new std::vector<Time*>();
    activeGun = 0;
    
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
    delete gunsOff; //ToDo: cuando borras un vector de punteros los punteros se quedan en memoria, habria que arreglar eso
    delete gunsCooldown;
    delete playerHP;
    delete bossHP;
    delete flash;
    delete flashCooldown;
    delete die;

    delete clockFlash;

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

    textSprite = NULL;
    talker = NULL;
    currentText = NULL;

    lifePlayerText = NULL;

    buttonDie = NULL;
}

void HUD::addGun(Coordinate position, Rect<float> rect, Rect<float> rectOff, Time *g){
    Sprite *temp = new Sprite(tex, rect);
    Sprite *tempOff = new Sprite(tex, rectOff);
    Sprite *tempCd = new Sprite(tex, *cooldownRect);
    
    temp->setPosition(position);
    tempOff->setPosition(position);
    tempCd->setPosition(position);
    
    tempCd->setSize(0,0);
    
    guns->push_back(temp);
    gunsOff->push_back(tempOff);
    gunsCooldown->push_back(tempCd);
    
    gunTimers->push_back(g);
    gunsModuleEnabled = true;
}

void HUD::setFlash(Rect<float> rect, Time *f){
    flash = new Sprite(tex, Rect<float>(rect.x, rect.y+80, rect.w, rect.h));
    flash->setPosition(100.0f,18.0f);
    flashCooldown = new Sprite(tex, Rect<float>(rect.x+80, rect.y+80, rect.w, rect.h));
    flashCooldown->setPosition(100.0f,18.0f);
    clockFlash = f;
    //timeFlash = f->getTime();
    flashModuleEnabled = true;
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
    if (gun >= 0 && gun < guns->size()) activeGun = gun;
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

bool HUD::drawHUD(bool onRange){
    Game::Instance()->window->draw(*hud->getSprite());
    drawPlayerHP();
    if (bossModuleEnable && onRange == true) drawBossHP(); 
    if (gunsModuleEnabled) {
        drawGun();
        drawGunCooldown();
    }
    if (flashModuleEnabled) {
        drawFlash();
        drawFlashCooldown();
    }
}

void HUD::drawGun(){
    for (int i = 0; i < guns->size(); i++){
        if (activeGun == i){
            Game::Instance()->window->draw(*guns->at(i)->getSprite());
        } else {
            Game::Instance()->window->draw(*gunsOff->at(i)->getSprite());
        }
    }
}

void HUD::drawPlayerHP(){
    Game::Instance()->window->draw(*playerHP->getSprite());
    Game::Instance()->window->draw(*lifePlayerText->getText());
}

void HUD::drawBossHP(){
    Game::Instance()->window->draw(*bossHP->getSprite());
}

void HUD::drawFlash(){
    Game::Instance()->window->draw(*flash->getSprite());
}

void HUD::drawFlashCooldown(){
    if(clockFlash->getTime() < clockFlash->getMaxTime()){
        flashCooldown->setSize(flashCooldown->getActualSpriteRect()->w-(flashCooldown->getOriginalSpriteRect()->w/(Game::Instance()->fps*clockFlash->getMaxTime())), 
                flashCooldown->getActualSpriteRect()->h);
    } else {
        clockFlash->pause();
    }
    if (clockFlash->isRunning()) Game::Instance()->window->draw(*flashCooldown->getSprite());
}

void HUD::drawGunCooldown(){
    for (int i=0; i<guns->size(); i++){
        if(gunTimers->at(i)->isRunning()){
            gunsCooldown->at(i)->setSize(gunsCooldown->at(i)->getActualSpriteRect()->w-
                ((gunsCooldown->at(i)->getOriginalSpriteRect()->w/gunTimers->at(i)->getMaxTime())/Game::Instance()->fps), 
                gunsCooldown->at(i)->getActualSpriteRect()->h);
            Game::Instance()->window->draw(*gunsCooldown->at(i)->getSprite());
        }
    }
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

void HUD::resetClockGuns(){ 
    if (!gunTimers->at(activeGun)->isRunning()) {
        gunsCooldown->at(activeGun)->restoreSize();
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
