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
    //La limpieza se hace en CleanUp
}

void LevelState::Init(){
    Game *game = Game::Instance();
    
    /*****RESOURCES*****/
    game->rM->loadTexture("player", "resources/spritesRATH.png");
    game->rM->loadTexture("fire", "resources/fuego.png");
    game->rM->loadTexture("hud", "resources/hud.png");
    game->rM->loadTexture("hud-spritesheet", "resources/sprites_hud.png");
    game->rM->loadTexture("pause-background", "resources/pause-bg.png");
    game->rM->loadTexture("button-layout", "resources/button-layout.png");
    game->rM->loadFont("font", "resources/font.ttf");
    
    /*****INPUTS*****/
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
    
    game->iM->addAction("player-shortAttack", 
            thor::Action(sf::Mouse::Left, thor::Action::PressOnce) && thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    game->iM->addAction("player-longAttackStart", thor::Action(sf::Mouse::Left, thor::Action::Hold));
    game->iM->addAction("player-longAttackStop", thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    
    game->iM->addAction("player-gunAttack", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("pause", thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce));
    game->iM->addActionCallback("text", thor::Action(sf::Event::TextEntered), &onTextEntered);
    
    /*****PLAYER, WEAPON AND GUNS*****/
    rath = new Player(Coordinate(2700,4200), Coordinate(128, 128), 40);
    rath->setAnimations(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    rath->getAnimation()->addAnimation("die", Coordinate(0, 512), 1, 0.5f);
    rath->setMaxHP(700);
    
    Weapon *wep = new Weapon(Coordinate(2500,5300), Coordinate(128, 128), 1, 0.25f);
    
    rath->setWeapon(wep);

    Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 5);
    gunArm->setAnimation(game->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->addAnimation("armaIzq", Coordinate(128, 512), 1, 2.0f);
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
    rath->setPosition(Coordinate(5700, 11500));
    
    /*****LEVEL*****/
    level = new Level(1);
    
    /*****HUD*****/
    hud = new HUD(game->rM->getTexture("hud"), game->rM->getTexture("hud-spritesheet"), 
            Rect<float>(100,230,200,20), Rect<float>(190,10,90,90), game->rM->getFont("font"));
    hud->addGun(Coordinate(20, 20), Rect<float>(10,10,90,90), Rect<float>(0,0,90,90), gunArm->getGunCooldown());
    hud->changeMaxLifePlayer(rath->getMaxHP());
    hud->setBossLife(Rect<float>(100,230,200,20));
    hud->changeMaxLifeBoss(level->getBoss()->getMaxHP());
    
    /*****PAUSE MENU*****/
    pause = new Menu(game->rM->getTexture("pause-background"), game->rM->getTexture("button-layout"), 
            new Rect<float>(0,0,200,50), game->rM->getFont("font"));
    pause->addButton(Coordinate(540,200), "Continuar", sf::Color::Black, sf::Color::Transparent, 20);
    pause->addButton(Coordinate(540,270), "Sonido On/Off", sf::Color::Black, sf::Color::Transparent, 20);
    pause->addButton(Coordinate(540,340), "Salir al menu", sf::Color::Black, sf::Color::Transparent, 20);
    paused = false;
}

void LevelState::Update(){
    if (!paused){

        float angleBoss = tri->angle(*level->getBoss()->getCoordinate(),*rath->getCoordinate());
        Coordinate newBoss = Coordinate(level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
                level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
        level->getBoss()->getCurrentGun()->update(newBoss, angleBoss);
        
        rath->getWeapon()->detectCollisions(Game::Instance()->mouse); //ToDo: cambiar el mouse por las  hitbox de los enemigos

        level->Update(rath, hud);
        /*if(level->getMap()->colision(rath->getHitbox()) != -1){
            if(rath->getHitbox()->hitbox->left <= level->getMap()->getColHitbox()->hitbox->left){
                colX=(rath->getHitbox()->hitbox->left +128 - level->getMap()->getColHitbox()->hitbox->left)*-1;
            } else {
                colX=((level->getMap()->getColHitbox()->hitbox->left + level->getMap()->getColHitbox()->hitbox->width)
                        - rath->getHitbox()->hitbox->left);
            }
            if(rath->getHitbox()->hitbox->top <= level->getMap()->getColHitbox()->hitbox->top){
                colY=(rath->getHitbox()->hitbox->top + 128 - level->getMap()->getColHitbox()->hitbox->top)*-1;
            }
            else{
                colY=((level->getMap()->getColHitbox()->hitbox->top + level->getMap()->getColHitbox()->hitbox->height)  
                        - rath->getHitbox()->hitbox->top);
            }
            
            cout << "colX: " << colX << endl;
            cout << "colY: " << colY << endl;
            cout << "Width map: " << level->getMap()->getColHitbox()->hitbox->width << endl;
            cout << "Left map: " << level->getMap()->getColHitbox()->hitbox->left << endl;
            cout << "Prueba rath: " << rath->getHitbox()->hitbox->left << endl;
            
            //rath->move(colX/rath->getSpeed(), colY/rath->getSpeed());
            if(prueba=="x"){
                rath->move(colX/rath->getSpeed(), 0);
            }
            if(prueba=="y"){
                rath->move(0, colY/rath->getSpeed());
            }
        }*/
    }
}

void LevelState::Input(){

    if (Game::Instance()->iM->isActive("pause")) {
        if (paused == true) paused = false;
        else paused = true;
    }
    if (!paused){
        /*Player movement*/
        rath->getState()->update();
        if (Game::Instance()->iM->isActive("player-up-left")) { 
            rath->move(-1, -1);
        } else if(Game::Instance()->iM->isActive("player-up-right")) {
            rath->move(1,-1);
        } else if(Game::Instance()->iM->isActive("player-down-left")) { 
            rath->move(-1,1);
        } else if(Game::Instance()->iM->isActive("player-down-right")) {
            rath->move(1,1);
        } else if (Game::Instance()->iM->isActive("player-up")) {
            prueba = "y";
            rath->move(0,-1);
        } else if (Game::Instance()->iM->isActive("player-down")) {
            prueba = "y";
            rath->move(0,1);
        } else if (Game::Instance()->iM->isActive("player-left")) {
            prueba = "x";
            rath->move(-1,0);
        } else if (Game::Instance()->iM->isActive("player-right")) {
            prueba = "x";
            rath->move(1,0);
        } else {
            rath->move(0,0);
        }

        /*Player gun rotation*/
        float mouseAng = tri->angleWindow(Coordinate(Game::Instance()->mouse->hitbox->left, Game::Instance()->mouse->hitbox->top));
        Coordinate newPos = Coordinate(rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
                rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
        rath->getCurrentGun()->update(newPos, mouseAng);

        /*Player weapon attack*/
        if (Game::Instance()->iM->isActive("player-shortAttack")){ //ToDo: hacemos que se ralentize al cargar?
            rath->weaponShortAttack(mouseAng);
        }
        if (Game::Instance()->iM->isActive("player-longAttackStart")){
            rath->weaponChargeAttack(mouseAng);
        }
        if (Game::Instance()->iM->isActive("player-longAttackStop")){
            rath->weaponReleaseAttack();
        }

        /*Player gun attack*/
        //ToDo: nada mas cargar el juego, la primera vez hace falta pulsar 2 veces (Bug)
        if(Game::Instance()->iM->isActive("player-gunAttack") && !rath->isAttacking()){ 
            hud->resetClockGuns();
            rath->gunAttack();
            rath->getCurrentGun()->getBullet()->setPosition(*rath->getCurrentGun()->getCoordinate());
        }
        
        level->Input(rath, hud);
        
    } else {
        /*Pause menu*/
        pause->checkHover(Game::Instance()->mouse);
        
        if (Game::Instance()->iM->isActive("click")){
            int clicks = pause->checkClicks();
            switch (clicks){
                case 0:
                    paused = false;
                break;
                case 1:
                    
                break;
                case 2:
                    Game::Instance()->ChangeCurrentState("menu");
                break;
                default: break;
            }
        }
    }
}

void LevelState::Render(){
    /*Update animators*/
    rath->getAnimation()->updateAnimator();
    rath->getCurrentGun()->getAnimation()->updateAnimator();
    rath->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    
    /*Interpolate*/
    if (*rath->getState()->getLastCoordinate() != *rath->getState()->getNextCoordinate()){
        Coordinate inc(rath->getState()->getIC());
        rath->setPosition(Coordinate(inc.x, inc.y));
    }
    
    /***Set View***/
    Game::Instance()->cameraView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->setView(Game::Instance()->cameraView);
    
    /*Render level*/
    level->Render();
    
    level->getMap()->putHitbox(rath);
    
    /*Render Player and guns*/
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
    if (!rath->getCurrentGun()->getBulletLifetime()->isExpired())
        Game::Instance()->window->draw(*rath->getCurrentGun()->getBullet()->getAnimation()->getSprite());
    else if (rath->isAttacking())
        rath->attackDone();
    
    if (rath->getWeapon()->isAttacking()) Game::Instance()->window->draw(*rath->getWeapon()->getPie()->getShape());
    
    /*Set Default View*/
    Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
    
    /*HUD*/
    hud->drawHUD(level->getBoss()->getOnRange());
    
    /*Texto NPC */
    if(level->getMuestra()==true){
        hud->drawTextLayer();
    }
    
    
    /*Pause*/
    if (paused) pause->drawMenu();
}

void LevelState::CleanUp(){
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
