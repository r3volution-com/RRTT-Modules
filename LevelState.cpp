#include "LevelState.h"
#include "Game.h"
#include "Crystal.h"
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
    
    //El juego no inicia pausado
    paused = false;
    
    /*****RESOURCES*****/
    game->rM->loadTexture("player", "resources/spritesRATH.png");
    game->rM->loadTexture("hud-spritesheet", "resources/sprites_hud.png");
    game->rM->loadTexture("hud-playerdeath", "resources/die.png");
    game->rM->loadTexture("pause-background", "resources/pause-bg.png");
    game->rM->loadTexture("damage","resources/dano.png");
    game->rM->loadTexture("laser","resources/rayo.png");
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
    
    game->iM->addAction("interact", thor::Action(sf::Keyboard::Key::E, thor::Action::PressOnce));
    
    game->iM->addAction("player-shortAttack", thor::Action(sf::Mouse::Left, thor::Action::PressOnce) && !thor::Action(sf::Mouse::Left, thor::Action::Hold));
    game->iM->addAction("player-longAttackStart", thor::Action(sf::Mouse::Left, thor::Action::Hold) && !thor::Action(sf::Mouse::Left, thor::Action::PressOnce));
    game->iM->addAction("player-longAttackStop", thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce));
    
    game->iM->addAction("player-gunAttack", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("pause", thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce));
    
    /* SONIDOS */
    game->rM->loadSound("ataque", "resources/ataque.ogg");
    game->rM->loadSound("cargar", "resources/cargar.ogg");
    game->rM->loadSound("fire", "resources/lanzallamas2.ogg");
    game->rM->loadSound("flash", "resources/flash.ogg");
    game->rM->loadSound("damage", "resources/damage.ogg");
    game->rM->loadSound("takeNote", "resources/takeNote.ogg");
    game->rM->loadMusic("boss", "resources/boss.ogg");
    game->rM->getMusic("boss")->getMusic()->setLoop(true);
    
    /*****PLAYER, WEAPON AND GUNS*****/
    rath = new Player(Coordinate(3950,14250), Coordinate(64, 100), 40);
    rath->setAnimations(game->rM->getTexture("player"), Rect<float>(0,0, 128, 128));
    rath->setMaxHP(350);
    rath->setFlashCooldown(2);
    rath->setFlashRange(10);
    
    Weapon *wep = new Weapon(Coordinate(2500,5300), Coordinate(128, 128), 1, 0.25f);
    wep->setDamage(12);
    rath->setWeapon(wep);
    
    rath->setPosition(Coordinate(0, 0));
      
    /*****HUD*****/
    hud = new HUD(game->rM->getTexture("hud-spritesheet"), 
            Rect<float>(1,200,205,20), Rect<float>(170,85,82,82), game->rM->getFont("font"));
    hud->changeMaxLifePlayer(rath->getMaxHP());
    hud->setBossLife(Rect<float>(5,200,200,20));
    hud->setFlash(Coordinate(20, 110), Rect<float>(170, 0, 82, 82), rath->getFlashCooldown());
    hud->setDieScreen(game->rM->getTexture("hud-playerdeath"), Coordinate(550, 320), game->rM->getTexture("gui-tileset"), Rect<float>(511, 925, 200, 64));
    
    /*****PAUSE MENU*****/
    pause = new Menu(game->rM->getTexture("pause-background"), game->rM->getTexture("gui-tileset"), 
            new Rect<float>(511,925,200,64), game->rM->getFont("font"));
    pause->addButton(Coordinate(550,250), "Continuar", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pause->addButton(Coordinate(550,320), "Guardar partida", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pause->addButton(Coordinate(550,390), "Salir al menu", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    pauseMenu = false;
    
    /*****DAMAGE*****/
    damage = new Sprite(game->rM->getTexture("damage"),Rect<float>(0, 0, 1280, 720));
     
    /*****LEVEL*****/
    /*Creamos el nivel*/
    level = new Level(rath, hud); 
    //Y lo iniciamos
    currentLevel = 1;
    level->Init(currentLevel);
    hud->changeMaxLifeBoss(level->getBoss()->getMaxHP());
    //std::cout<<level->getBoss()->getMaxHP()<<"\n";
}

void LevelState::Update(){
    if (!paused){
        if(rath->getDmgOnPlayer()->getTime() > 0){
            Game::Instance()->rM->getSound("damage")->getSound()->play();
        }
        rath->getWeapon()->update();
    }
    level->Update();
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
            
        float mouseAng = tri->angleWindow(Coordinate(Game::Instance()->mouse->hitbox->left, Game::Instance()->mouse->hitbox->top));

        /*Player weapon attack*/
        if (Game::Instance()->iM->isActive("player-shortAttack")){
            Game::Instance()->rM->getSound("ataque")->getSound()->play();
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

        if (rath->getGunNumber() >= 0){
            /*Player gun rotation*/
            Coordinate newPos = Coordinate(rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
                    rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
            rath->getCurrentGun()->update(newPos, mouseAng);
            //std::cout << "YAY\n";
            /*Player gun attack*/
            //ToDo: nada mas cargar el juego, la primera vez hace falta pulsar 2 veces (Bug)
            if(Game::Instance()->iM->isActive("player-gunAttack") && !rath->isAttacking()){
                if (rath->getCurrentGun()->getGunCooldown()->getTime()==5 || rath->getCurrentGun()->getGunCooldown()->getTime()==0) Game::Instance()->rM->getSound("fire")->getSound()->play();
                hud->resetClockGuns();
                rath->gunAttack();
                rath->getCurrentGun()->getBullet()->setPosition(*rath->getCurrentGun()->getCoordinate());
            }
        }
        
        /*Player Flash*/
        if (Game::Instance()->iM->isActive("player-flash") && rath->getFlashCooldown()->getTime()==0
                && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::D))){
            //cout << rath->getFlashCooldown()->getTime() << endl;
            Game::Instance()->rM->getSound("flash")->getSound()->play();
            hud->resetClockFlash();
            rath->flash();
        }
        //Pausar la partida si rath muere
        if (rath->isDead()) {
            hud->playerDie();
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
                           //ToDo: GUARDAR PARTIDA AQUI FOLKLORE
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
                Game::Instance()->rM->getMusic("boss")->getMusic()->stop();
                Game::Instance()->getLevelState()->getLevel()->setPlay(false);
                Game::Instance()->rM->getMusic("Main")->getMusic()->play();
                
                level->getBoss()->setPosition(*level->getBoss()->getInitialCoordinate());
                level->getBoss()->setHP(level->getBoss()->getMaxHP());
                hud->changeLifeBoss(level->getBoss()->getHP());
                
                level->setBossZone(false);
                
                rath->respawn();
                
                hud->changeLifePlayer(rath->getHP());
                
                paused = false;
            }
        }
    }
    level->Input();
}

void LevelState::Render(){
    /*Update animators*/
    rath->getAnimation()->updateAnimator();
    if (rath->getGunNumber() >= 0){
        rath->getCurrentGun()->getAnimation()->updateAnimator();
        rath->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    }
    
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
    if (rath->getGunNumber() >= 0){
        Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
        if (!rath->getCurrentGun()->getBulletLifetime()->isExpired())
            Game::Instance()->window->draw(*rath->getCurrentGun()->getBullet()->getAnimation()->getSprite());
        else if (rath->isAttacking())
            rath->attackDone();
    }
    
    if (rath->getWeapon()->isAttacking()) Game::Instance()->window->draw(*rath->getWeapon()->getPie()->getShape());
    
    /*Set Default View*/
    Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
    
    /*Damage*/
    if(rath->getDmgOnPlayer()->getTime() > 0){
        Game::Instance()->window->draw(*damage->getSprite());
    }
    
    /*HUD*/
    hud->drawHUD(level->getBoss()->getOnRange());
      
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

void LevelState::changeLevel(){
    currentLevel++;
    level->CleanUp();
    level->Init(currentLevel);
}