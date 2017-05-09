#include "LevelState.h"
#include "Game.h"
#include "Crystals.h"
#include "Level.h"
#include "Console.h"
#include "libs/Pie.h"

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
    
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
    
    game->iM->addAction("player-shortAttack", thor::Action(sf::Mouse::Left, thor::Action::PressOnce));
    game->iM->addAction("player-longAttackStart", thor::Action(sf::Mouse::Left, thor::Action::Hold));
    game->iM->addAction("player-longAttackStop", thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    
    game->iM->addAction("player-gunAttack", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("console", thor::Action(sf::Keyboard::F12, thor::Action::PressOnce));
    game->iM->addActionCallback("text", thor::Action(sf::Event::TextEntered), &onTextEntered);
    
    /*****PLAYER*****/
    rath = new Player(Coordinate(140,1000), Coordinate(128, 128), 15);
    rath->setAnimations(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    rath->getAnimation()->addAnimation("die", Coordinate(0, 512), 1, 0.5f);
    rath->setMaxHP(70);
    
    Weapon *wep = new Weapon(Coordinate(140,1000), Coordinate(128, 128), 1);
    
    rath->setWeapon(wep);

    Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 5);
    gunArm->setAnimation(game->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    gunArm->getAnimation()->setOrigin(Coordinate(56,34));
    gunArm->setDamage(1);
    
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
    
    hud = new HUD(game->rM->getTexture("hud"), game->rM->getTexture("hud-spritesheet"), Rect<float>(100,230,200,20), Rect<float>(190,10,90,90), game->rM->getFont("font"));
    hud->addGun(Coordinate(20, 20), Rect<float>(10,10,90,90), Rect<float>(0,0,90,90), gunArm->getGunCooldown());
    hud->changeMaxLifePlayer(rath->getMaxHP());
}

void LevelState::Update(){
    level->AI(rath,hud);
    std::vector<Enemy*> *enemys = level->getEnemys();  //ToDo: trasladar a level
    for(int i = 0; i < enemys->size(); i++){
        if (enemys->at(i)->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
            enemys->at(i)->damage(rath->getCurrentGun()->getDamage());
        }
    }
}

void LevelState::Input(){ //ToDo: para pausa se tiene un boolean que engloba todo update y casi todo input (excepto la llamada para cerrar el propio menu de pausa)
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
    Coordinate newPos = Coordinate(rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
            rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
    rath->getCurrentGun()->update(newPos, mouseAng);
    
    float angleBoss = tri->angle(*level->getBoss()->getCoordinate(),*rath->getCoordinate());
    Coordinate newBoss = Coordinate(level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
            level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
    level->getBoss()->getCurrentGun()->update(newBoss, angleBoss);
    
                
    /*Player weapon attack*/
    if (Game::Instance()->iM->isActive("player-shortAttack")){
        rath->weaponShortAttack(mouseAng);
    }
    if (Game::Instance()->iM->isActive("player-longAttackStart")){
        rath->weaponChargeAttack(mouseAng);
    }
    if (Game::Instance()->iM->isActive("player-longAttackStop")){
        //rath->weaponReleaseAttack();
    }
    
    /*Player gun attack*/
    if(Game::Instance()->iM->isActive("player-gunAttack") && !rath->isAttacking()){ //ToDo: nada mas cargar el juego, la primera vez hace falta pulsar 2 veces (Bug)
        hud->resetClockGuns();
        rath->gunAttack();
        rath->getCurrentGun()->getBullet()->setPosition(*rath->getCurrentGun()->getCoordinate());
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
    
    level->Render();
    
    level->map->putHitbox(rath);
    
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
    if (!rath->getCurrentGun()->getBulletLifetime()->isExpired()){
        Game::Instance()->window->draw(*rath->getCurrentGun()->getBullet()->getAnimation()->getSprite());
    } else if (rath->isAttacking()){
        rath->attackDone();
    }
    if (rath->getWeapon()->isAttacking()) {
       // std::cout << "YAY\n";
        Game::Instance()->window->draw(*rath->getWeapon()->getPie()->getShape());
       // std::cout << "YEY\n";
    }
    
    /*HUD*/
    Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
    hud->drawHUD();
    Game::Instance()->console->drawConsole();
}

void LevelState::CleanUp(){
    
}
