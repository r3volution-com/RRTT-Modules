#include "LevelState.h"
#include "Game.h"
#include "Crystals.h"
#include "Level.h"
#include "Console.h"

#define PI 3,14159265;

void onTextEntered(thor::ActionContext<std::string> context) {
    if (Game::Instance()->console->isActive()){
        if (context.event->text.unicode < 128 && (context.event->text.unicode != 13 && context.event->text.unicode != 9 && context.event->text.unicode != 8)) {
            sf::Uint32 character = context.event->text.unicode;
            std::ostringstream ch;
            ch << static_cast<char>(character);
            Game::Instance()->temp += ch.str();
            //Game::Instance()->temp << (std::string)ch.str();
            Game::Instance()->console->writeCommand(Game::Instance()->temp);
        } else if (context.event->text.unicode == 8 && Game::Instance()->temp.length() > 0){
            Game::Instance()->temp.resize(Game::Instance()->temp.length()-1);
            Game::Instance()->console->writeCommand(Game::Instance()->temp);
        } else if (context.event->text.unicode == 13){
            Game::Instance()->console->sendCommand(Game::Instance()->temp);
            Game::Instance()->temp = "";
        }
    }
}

LevelState::LevelState() : GameState(){
    tri = new Trigonometry();
}

LevelState::~LevelState(){
    delete rath;
    delete tri;
    
    /*Faltaria:
        - playerTexture
     *  - level
     *  - enemy2
     *  - hud 
     */  

    rath = NULL;
    tri = NULL;
}

void LevelState::Init(){
    Game *game = Game::Instance();
    /*****RESOURCES*****/
    game->rM->loadTexture("player", "resources/spritesRATH.png");
    game->rM->loadTexture("fire", "resources/fuego.png"); //ToDo: otra spritesheet para ataques?
    game->rM->loadTexture("hud", "resources/hud.png");
    game->rM->loadTexture("hud-spritesheet", "resources/sprites_hud.png");
    game->rM->loadFont("font", "resources/font.ttf");
    
    /*****PLAYER*****/
    rath = new Player(Coordinate(3900,2700), Coordinate(128, 128), 15);
    rath->setAnimations(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    rath->setMaxHP(70);
    
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    game->iM->addAction("player-Lclick", thor::Action(sf::Mouse::Left));
    
    game->iM->addAction("player-Rclick", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
    
    game->iM->addAction("console", thor::Action(sf::Keyboard::F12, thor::Action::PressOnce));
    game->iM->addActionCallback("text", thor::Action(sf::Event::TextEntered), &onTextEntered);

    Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 5);
    gunArm->setAnimation(game->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    gunArm->getAnimation()->setOrigin(Coordinate(56,34));
    gunArm->setDamage(30);
    
    Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2);
    bull->setAnimation(game->rM->getTexture("fire"), Rect<float>(0,0, 128, 128));
    bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 0), 2, 0.5f);
    bull->getAnimation()->setOrigin(Coordinate(184,98));
    bull->getAnimation()->initAnimator();
    bull->getAnimation()->changeAnimation("fireIdle", false);
    
    gunArm->setAttack(bull);
    
    rath->addGun(gunArm);
    rath->changeGun(0);
    
    level = new Level(1);
    
    hud = new HUD(game->rM->getTexture("hud"), game->rM->getTexture("hud-spritesheet"), Rect<float>(100,100,120,20), Rect<float>(190,10,90,90), game->rM->getFont("font"));
    hud->addGun(Coordinate(20, 20), Rect<float>(10,10,90,90), Rect<float>(0,0,90,90), gunArm->getGunCooldown());
}

void LevelState::Update(){
    level->enemyAI(rath);
    std::vector<Enemy*> *enemys = level->getEnemys();  //ToDo: trasladar a level
    for(int i = 0; i < enemys->size(); i++){
        if (enemys->at(i)->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox())){
            enemys->at(i)->damage(rath->getCurrentGun()->getDamage());
        }
    }
}

void LevelState::Input(){
    rath->getState()->update();
    /*Player movement*/
    if (Game::Instance()->iM->isActive("player-up-left")) { 
        /*if(level->map->putHitbox(rath)==true){
            colision='q'; 
            rath->move(1,1);
        }
        if(level->map->putHitbox(rath)==false && colision!='q'){
            rath->move(-1,-1);
            colision='z';
        } */
        rath->move(-1, -1);
    } else if(Game::Instance()->iM->isActive("player-up-right")) {
        rath->move(1,-1);
    } else if(Game::Instance()->iM->isActive("player-down-left")) { 
        rath->move(-1,1);
    } else if(Game::Instance()->iM->isActive("player-down-right")) {
        rath->move(1,1);
    } else if (Game::Instance()->iM->isActive("player-up")) {
        rath->move(0,-1);
    } else if (Game::Instance()->iM->isActive("player-down")) {
        rath->move(0,1);
    } else if (Game::Instance()->iM->isActive("player-left")) {
        rath->move(-1,0);
    } else if (Game::Instance()->iM->isActive("player-right")) {
        rath->move(1,0);
    } else {
        rath->move(0,0);
    }
    
    /*Player gun rotation*/
    float mouseAng = tri->angleWindow(Coordinate(Game::Instance()->mouse->hitbox->left, Game::Instance()->mouse->hitbox->top));
    Coordinate newPos = Coordinate(rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
    rath->getCurrentGun()->update(newPos, mouseAng);
    
                
    /*Player weapon attack*/
    if (Game::Instance()->iM->isActive("player-Lclick") && !rath->isAttacking()){ //ToDo: creo que deberia haber una clase weapon por que su funcionamiento es diferente a las armas
        rath->weaponAttack();//ToDo: lo de debajo se puede meter aqui pasando angulo por parametro
        if(mouseAng < 315 && mouseAng > 225){ //Derecha
            rath->getAnimation()->changeAnimation("ataqueDerecha", true);
        } else if (mouseAng < 225 && mouseAng > 135){ //Arriba
            rath->getAnimation()->changeAnimation("ataqueArriba", true);
        } else if (mouseAng < 135 && mouseAng > 45){ //Izquierda
            rath->getAnimation()->changeAnimation("ataqueIzquierda", true);
        } else if (mouseAng < 45 || mouseAng > 315){ //Abajo
            rath->getAnimation()->changeAnimation("ataqueAbajo", true);
        }
    } else {
        rath->getAnimation()->queueAnimation("idle", false); //ToDo: esto se puede ejecutar al acabar el timer del ataque
    }
    
    /*Player gun attack*/
    if(Game::Instance()->iM->isActive("player-Rclick")){
        hud->resetClockGuns();
        rath->gunAttack();
        rath->getCurrentGun()->getBullet()->setPosition(*rath->getCoordinate());
    }
    
    /*Console*/
    if (Game::Instance()->iM->isActive("console")) Game::Instance()->console->toggleActive();
}

void LevelState::Render(){
    /*Update animators*/
    rath->getAnimation()->updateAnimator();
    rath->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    
    /*Interpolate*/
    Coordinate inc(rath->getState()->getIC());
    rath->setPosition(Coordinate(inc.x, inc.y));
    
    /***RENDER***/
    Game::Instance()->cameraView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->setView(Game::Instance()->cameraView);
    
    level->drawAll();
    
    level->map->putHitbox(rath);
    
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
    if (!rath->getCurrentGun()->getBulletLifetime()->isExpired()){
        Game::Instance()->window->draw(*rath->getCurrentGun()->getBullet()->getAnimation()->getSprite());
    }
    /*HUD*/
    Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
    Game::Instance()->console->drawConsole();
    hud->drawHUD();
}

void LevelState::CleanUp(){
    
}