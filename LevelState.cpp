#include "LevelState.h"
#include "Game.h"
#include "Crystals.h"
#include "Level.h"
#include "Console.h"
#include "libs/Pie.h"
 
#define PI 3,14159265;

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
    game->rM->loadTexture("hud-spritesheet", "resources/sprites_hud.png");
    game->rM->loadTexture("hud-playerdeath", "resources/die.png");
    game->rM->loadTexture("pause-background", "resources/pause-bg.png");
    game->rM->loadTexture("damage","resources/dano.png");
    game->rM->loadFont("font", "resources/font.ttf");
    
    /*****INPUTS*****/
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::W));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::S));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::D));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::A));
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::A) && thor::Action(sf::Keyboard::W));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::D) && thor::Action(sf::Keyboard::W));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::A) && thor::Action(sf::Keyboard::S));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::D) && thor::Action(sf::Keyboard::S));
    
    game->iM->addAction("player-flash", thor::Action(sf::Keyboard::F));
    
    game->iM->addAction("player-shortAttack", 
            thor::Action(sf::Mouse::Left, thor::Action::PressOnce) && thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    game->iM->addAction("player-longAttackStart", thor::Action(sf::Mouse::Left, thor::Action::Hold));
    game->iM->addAction("player-longAttackStop", thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    
    game->iM->addAction("player-gunAttack", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("pause", thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce));
    
    /*****PLAYER, WEAPON AND GUNS*****/
    rath = new Player(Coordinate(5500,14250), Coordinate(128, 128), 40);
    rath->setAnimations(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    rath->setMaxHP(350);
    rath->setFlashCooldown(2);
    rath->setFlashRange(10);
    //rath->getAnimation()->getSprite()->setScale(1.5f, 1.5f);
    
    Weapon *wep = new Weapon(Coordinate(2500,5300), Coordinate(128, 128), 1, 0.25f);
    wep->setDamage(12);
    
    rath->setWeapon(wep);

    Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 5);
    gunArm->setAnimation(game->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->addAnimation("armaIzq", Coordinate(128, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    gunArm->getAnimation()->setOrigin(Coordinate(56,34));
    gunArm->setDamage(2);
    
    Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2);
    bull->setAnimation(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    bull->getAnimation()->addAnimation("fireIdle", Coordinate(128, 896), 2, 0.5f);
    bull->getAnimation()->setOrigin(Coordinate(184,98));
    bull->getAnimation()->initAnimator();
    bull->getAnimation()->changeAnimation("fireIdle", false);
    
    gunArm->setAttack(bull);
    
    rath->addGun(gunArm);
    rath->changeGun(0);
    rath->setPosition(Coordinate(5500, 14250));
     
    /*****LEVEL*****/
    level = new Level(1);
    
    /*****HUD*****/
    hud = new HUD(game->rM->getTexture("hud-spritesheet"), 
            Rect<float>(5,200,200,20), Rect<float>(170,85,82,82), game->rM->getFont("font"));
    hud->addGun(Coordinate(20, 20), Rect<float>(85,0,82,85), Rect<float>(85,0,82,82), gunArm->getGunCooldown());
    hud->changeMaxLifePlayer(rath->getMaxHP());
    hud->setBossLife(Rect<float>(5,200,200,20));
    hud->changeMaxLifeBoss(level->getBoss()->getMaxHP());
    hud->setFlash(Coordinate(20, 110), Rect<float>(170, 0, 82, 82), rath->getFlashCooldown());
    hud->setDieScreen(game->rM->getTexture("hud-playerdeath"), Coordinate(550, 320), game->rM->getTexture("gui-tileset"), Rect<float>(511, 925, 200, 64));
    
    /*****PAUSE MENU*****/
    pause = new Menu(game->rM->getTexture("pause-background"), game->rM->getTexture("gui-tileset"), 
            new Rect<float>(511,925,200,64), game->rM->getFont("font"));
    pause->addButton(Coordinate(550,250), "Continuar", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pause->addButton(Coordinate(550,320), "Sonido On/Off", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pause->addButton(Coordinate(550,390), "Salir al menu", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pauseMenu = false;
    
    paused = false;
    
    /*****DAMAGE*****/
    damage = new Sprite(game->rM->getTexture("damage"),Rect<float>(0, 0, 1280, 720));
}

void LevelState::Update(){
    level->setDisNpcPlayer(level->getTrignometry()->distance(*rath->getCoordinate(), *level->getNPC()->getCoordinate()));
    
    if(level->getMoverse()==true){
        if(level->getNPC()->getCoordinate()->y < 20000){
            level->getNPC()->move(0,20);
        }else{
            paused = false;
            level->setMoverse(false);
        }if(level->getDisNpcPlayer() > 1000){
            paused = false;
        }
    }
    
    if (!paused){
        float angleBoss = tri->angle(*level->getBoss()->getCoordinate(),*rath->getCoordinate());
        Coordinate newBoss = Coordinate(level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
                level->getBoss()->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
        level->getBoss()->getCurrentGun()->update(newBoss, angleBoss);
        
        rath->getWeapon()->detectCollisions(Game::Instance()->mouse); //ToDo: cambiar el mouse por las  hitbox de los enemigos

        level->Update(rath, hud);
    }else {
        
    }
}

void LevelState::Input(){
    if (Game::Instance()->iM->isActive("pause")) {
        if (paused == true) {
            paused = false;
            pauseMenu = false;
        } else {
            paused = true;
            pauseMenu = true;
        }
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

        /*Player weapon attack*/
        if (Game::Instance()->iM->isActive("player-shortAttack")){ 
            rath->weaponShortAttack(mouseAng);
        }
        if (Game::Instance()->iM->isActive("player-longAttackStart")){//ToDo: hacemos que se ralentize al cargar?
            rath->weaponChargeAttack(mouseAng);
            rath->setSpeed(rath->getInitialSpeed() * 0.5);
        }
        if (Game::Instance()->iM->isActive("player-longAttackStop")){
            rath->weaponReleaseAttack();
            rath->setSpeed(rath->getInitialSpeed());
        }

        /*Player gun attack*/
        //ToDo: nada mas cargar el juego, la primera vez hace falta pulsar 2 veces (Bug)
        if(Game::Instance()->iM->isActive("player-gunAttack") && !rath->isAttacking()){ 
            hud->resetClockGuns();
            rath->gunAttack();
            rath->getCurrentGun()->getBullet()->setPosition(*rath->getCurrentGun()->getCoordinate());
        }
        
        /*Player Flash*/
        if (Game::Instance()->iM->isActive("player-flash")){
            hud->resetClockFlash();
            rath->flash();
        }
        
        level->Input(rath, hud);
     
        if (rath->isDead()) {
            hud->playerDie();
            cout << "Antes" << level->getSinSalida() << endl;
            level->setSinSalida(true);
            cout << "Despues" << level->getSinSalida() << endl;
            cout << "He muerto: " << level->getBoss()->getOnRange() << endl;
            paused = true;
        }
    } else {
        /*Pause menu*/
        if (pauseMenu){
            pause->checkHover(Game::Instance()->mouse);

            if (Game::Instance()->iM->isActive("click")){
                int clicks = pause->checkClicks();
                switch (clicks){
                    case 0:
                        paused = false;
                        pauseMenu = false;
                    break;
                    case 1:

                    break;
                    case 2:
                        return Game::Instance()->ChangeCurrentState("menu");
                    break;
                    default: break;
                }
            }
        }
        
        if (rath->isDead()){
            hud->playerDie();
            if(hud->getButton()->getHover() && Game::Instance()->iM->isActive("click")){
                if(level->getBoss()->getOnRange()){
                   rath->respawn(1); 
                }else{
                   rath->respawn(0); 
                }
                hud->changeLifePlayer(rath->getHP());
                level->getBoss()->setHP(level->getBoss()->getMaxHP());
                hud->changeLifeBoss(level->getBoss()->getHP());
                paused = false;
                Game::Instance()->getLevelState()->getLevel()->setSinSalida(true);
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
        rath->updatePosition(Coordinate(inc.x, inc.y));
    }
    
    /***Set View***/
    Game::Instance()->cameraView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->setView(Game::Instance()->cameraView);
    
    /*Render level*/
    level->Render();
    
    
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
    
    /*Damage*/
    if(rath->getDmgOnPlayer()->getTime() > 0){
        Game::Instance()->window->draw(*damage->getSprite());
    }
    
    /*HUD*/
    hud->drawHUD(level->getBoss()->getOnRange());
    
    /*Texto NPC */
    if(level->getMuestra()==true && rath->collision(Game::Instance()->getLevelState()->getLevel()->getNPC()->getHitbox())){
        hud->drawTextLayer();
    }else if(level->getMuestra()==true && !rath->collision(Game::Instance()->getLevelState()->getLevel()->getNPC()->getHitbox())){
        Game::Instance()->getLevelState()->getLevel()->setMuestra(false);
    }
    
    if(level->getShowIterationNpc() && level->getMuestra() == false && paused == false){
        Game::Instance()->window->draw(*level->getKeyIterationNpc()->getText());
    }
    
    /*Texto notas */
    if(level->getShowText()==true){
        Game::Instance()->window->draw(*level->getNote()->getBackgroundSprite()->getSprite());
        Game::Instance()->window->draw(*level->getNote()->getText()->getText());
    }
      
    /*Pause*/
    if (paused && pauseMenu) pause->drawMenu();
}

void LevelState::CleanUp(){
    Game::Instance()->rM->releaseTexture("player");
    Game::Instance()->rM->releaseTexture("hud");
    Game::Instance()->rM->releaseTexture("hud-spritesheet");
    Game::Instance()->rM->releaseTexture("hud-playerdeath");
    Game::Instance()->rM->releaseTexture("pause-background");
    Game::Instance()->rM->releaseFont("font");
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
