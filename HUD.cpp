#include "HUD.h"
#include "Game.h"

HUD::HUD(Texture *rTex, Rect<float> lRect, Rect<float> cdRect, Font *f){
    
    tex = rTex;
    font = f;
    
    cooldownRect = new Rect<float> (cdRect);
    
    //ToDo: la vida deberia ser modular
    playerHP = new Sprite(tex, lRect); 
    playerHP->setPosition(296.5f,30.0f);
    lifePlayerText = new Text(std::string(), Coordinate(0,0), font, false);
    lifePlayerText->setTextStyle(sf::Color::Black, 12);
    lifePlayerText->setOutlineStyle(sf::Color::Black, 0);
    maxLifePlayer = 100;
    lifePlayer = maxLifePlayer;
    //Fin

    activeGun = 0;
    
    dieBool = false;
    
    flashModuleEnabled = false;
    gunsModuleEnabled = false;
    dieModuleEnabled = false;
    textModuleEnabled = false;
    bossModuleEnable = false;
    textSprite = NULL;
    talker = NULL;
    currentText = NULL;
    lifePlayerText = NULL;
}

HUD::~HUD(){
    for (int i=0; i<guns.size(); i++){
        delete guns.at(i);
        guns.at(i) = NULL;
    }
    guns.clear();
    
    for (int i=0; i<gunsOff.size(); i++){
        delete gunsOff.at(i);
        gunsOff.at(i) = NULL;
    }
    gunsOff.clear();
    
    for (int i=0; i<gunsCooldown.size(); i++){
        delete gunsCooldown.at(i);
        gunsCooldown.at(i) = NULL;
    }
    gunsCooldown.clear();
    
    
    delete playerHP;
    delete bossHP;
    delete flash;
    delete flashCooldown;
    delete die;
    delete cooldownRect;
    //delete clockFlash; ToDo: da error

    if(textSprite != NULL)delete textSprite;
    if(talker != NULL)delete talker;
    if(currentText != NULL)delete currentText;

    if(lifePlayerText != NULL)delete lifePlayerText;

    //delete buttonDie; ToDo: da error
    
    playerHP = NULL;
    bossHP = NULL;
    flash = NULL;
    flashCooldown = NULL;
    die = NULL;
    cooldownRect = NULL;
    //clockFlash = NULL; 

    textSprite = NULL;
    talker = NULL;
    currentText = NULL;

    lifePlayerText = NULL;

    //buttonDie = NULL;
}

void HUD::addGun(Coordinate position, Rect<float> rect, Rect<float> rectOff, Time *g){
    Sprite *temp = new Sprite(tex, rect);
    Sprite *tempOff = new Sprite(tex, rectOff);
    Sprite *tempCd = new Sprite(tex, *cooldownRect);
    
    temp->setPosition(position);
    tempOff->setPosition(position);
    tempCd->setPosition(position);
    
    tempCd->setSize(0,0);
    
    guns.push_back(temp);
    gunsOff.push_back(tempOff);
    gunsCooldown.push_back(tempCd);
    
    gunTimers.push_back(g);
    gunsModuleEnabled = true;
}

void HUD::setFlash(Coordinate pos, Rect<float> rect, Time *f){
    flash = new Sprite(tex, Rect<float>(rect.x, rect.y, rect.w, rect.h));
    flash->setPosition(pos.x,pos.y);
    flashCooldown = new Sprite(tex, *cooldownRect);
    flashCooldown->setPosition(pos.x,pos.y);
    flashCooldown->setSize(0,0);
    clockFlash = f;
    //timeFlash = f->getTime();
    flashModuleEnabled = true;
}

void HUD::setDieScreen(Texture *dTex, Coordinate coor, Texture* tex, Rect<float> rect){
    die = new Sprite(dTex, Rect<float> (0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    buttonDie = new Button(coor, tex, rect);
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
    currentText->setTextStyle(fillColor, size);
    currentText->setOutlineStyle(outlineColor, 1);
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
    if (gun >= 0 && gun < guns.size()) activeGun = gun;
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

void HUD::drawHUD(bool onRange){
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
    if (dieModuleEnabled && dieBool && Game::Instance()->getLevelState()->getPaused()) {

        drawDie();
    }
}

void HUD::drawGun(){
    for (int i = 0; i < guns.size(); i++){
        if (activeGun == i){
            Game::Instance()->window->draw(*guns.at(i)->getSprite());
        } else {
            Game::Instance()->window->draw(*gunsOff.at(i)->getSprite());
        }
    }
}

void HUD::drawPlayerHP(){
    Game::Instance()->window->draw(*playerHP->getSprite());
}

void HUD::drawBossHP(){
    std::cout<<"si"<<"\n";
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
    for (int i=0; i<guns.size(); i++){
        if(gunTimers.at(i)->isRunning()){
            gunsCooldown.at(i)->setSize(gunsCooldown.at(i)->getActualSpriteRect()->w-
                ((gunsCooldown.at(i)->getOriginalSpriteRect()->w/gunTimers.at(i)->getMaxTime())/Game::Instance()->fps), 
                gunsCooldown.at(i)->getActualSpriteRect()->h);
            Game::Instance()->window->draw(*gunsCooldown.at(i)->getSprite());
        }
    }
}

void HUD::drawTextLayer(){
    Game::Instance()->window->draw(*textSprite->getSprite());
    Game::Instance()->window->draw(*talker->getText());
    Game::Instance()->window->draw(*currentText->getText());
}

void HUD::resetClockFlash(){
    if (!clockFlash->isRunning()){ 
        flashCooldown->restoreSize();
    }
}

void HUD::resetClockGuns(){ 
    if (!gunTimers.at(activeGun)->isRunning()) {
        gunsCooldown.at(activeGun)->restoreSize();
    }
}

void HUD::resetStats(){
    changeLifePlayer(maxLifePlayer);
    changeLifeBoss(maxLifeBoss);
    
    playerHP->restoreSize();
    bossHP->restoreSize();
    
    dieBool = false;
}

void HUD::drawDie(){
    if(lifePlayer <= 0){
        Game::Instance()->window->draw(*die->getSprite());
        buttonDie->draw();
    }
}

bool HUD::playerDie(){
    if (lifePlayer <= 0){
        if(dieBool == false){
            //sf::sleep(sf::seconds(1));
            dieBool = true;
            buttonDie->setText("Reintentar", sf::Color::White, font, 20);
            buttonDie->setOutline(1, sf::Color(170, 170, 170, 255), sf::Color::Transparent);
        } else {
            buttonDie->hover(Game::Instance()->mouse);
        }
    }
}
