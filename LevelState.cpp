#include "LevelState.h"
#include "Game.h"
#include "Crystals.h"
#include "Level.h"
#include "Console.h"

#define PI 3,14159265;

LevelState::LevelState() : GameState(){
    
}

LevelState::~LevelState(){
    
}

void LevelState::Init(){
    tri = new Trigonometry();
    level = new Level(1);
    
    Game *game = Game::Instance();
    
    game->rM->loadTexture("player", "resources/sprites.png");
    game->rM->loadTexture("console-bg", "resources/console-bg.png");
    game->rM->loadFont("console", "resources/font.ttf");
    
    rath = new Player(Coordinate(3900,2700), game->rM->getTexture("player"), Rect<float>(0,0, 128, 128), 15);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 4, 0.5f);
    rath->getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueAbajo", Coordinate(0, 1024), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueArriba", Coordinate(0, 1152), 2, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false); 
    rath->setMaxHP(70);
    
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    game->iM->addAction("player-Lclick", thor::Action(sf::Mouse::Left));
    
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
    
    game->iM->addAction("console", thor::Action(sf::Keyboard::F12));

    console = new Console(Coordinate(0,500), game->rM->getTexture("console-bg"), Rect<float>(0,0,1280,220), game->rM->getFont("console"));

    Gun *gunArm = new Gun(Coordinate(0, 0), Rect<float> (0, 640, 128, 128), game->rM->getTexture("player"));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    gunArm->getAnimation()->setOrigin(Coordinate(64,30));
    
    enemy2 = new Enemy(Coordinate(2500,2300), game->rM->getTexture("Bloque"), Rect<float>(0,0,512,512), 10);
    enemy2->getAnimation()->addAnimation("idle", Coordinate(0,0),1,10.0f);
    enemy2->getAnimation()->initAnimator();
    enemy2->getAnimation()->changeAnimation("idle",false);
    rath->addGun(gunArm);
   
    
}

void LevelState::Update(){
    
    level->enemyAI(rath);
    
}

void LevelState::Input(){
    Coordinate coor = Coordinate(Game::Instance()->mouse->hitbox->left, Game::Instance()->mouse->hitbox->top);
    float mouseAng = tri->angleWindow(coor);
    rath->getCurrentGun()->getAnimation()->setRotation(mouseAng);
        
    if (Game::Instance()->iM->isActive("player-up")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='a'; 
            rath->move(0,1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='a'){
            rath->move(0,-1);
            colision='z';
        }
        if(direcNow!='u'){
            rath->getAnimation()->changeAnimation("correrArriba", false);
        }
        direcNow='u';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-down")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='b'; 
            rath->move(0,-1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='b'){
            rath->move(0,1);
            colision='z';
        }
        if(direcX=='r' && direcNow!='d'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);  
            mov=true;
            direcNow='d';
        } else if(direcX=='l' && direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
            mov=true;
            direcNow='d';
        }
    }else if (Game::Instance()->iM->isActive("player-left")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='i'; 
            rath->move(1,0);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='i'){
            rath->move(-1,0);
            colision='z';
        }
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-right")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='d'; 
            rath->move(-1,0);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='d'){
            rath->move(1,0);
            colision='z';
        }        
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-Lclick")){
        if(mouseAng<315 && mouseAng>225 && ata == false){
                //derecha BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueDerecha", true);
                ata=true;
            }
            if(mouseAng<225 && mouseAng>135 && ata == false){
                //arriba BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueArriba", true);
                ata=true;
            }
            if(mouseAng<135 && mouseAng>45 && ata == false){
                //izquierda BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueIzquierda", true);
                ata=true;
            }
            if(mouseAng<45 || mouseAng>315 && ata == false){
                //abajo BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueAbajo", true);
                ata=true;
            }
    }else if(Game::Instance()->iM->isActive("player-up-left")){ 
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='q'; 
            rath->move(1,1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='q'){
            rath->move(-1,-1);
            colision='z';
        } 
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-up-right")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='w'; 
            rath->move(-1,1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='w'){
            rath->move(1,-1);
            colision='z';
        } 
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-down-left")){ 
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='r'; 
            rath->move(1,-1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='r'){
            rath->move(-1,1);
            colision='z';
        } 
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-down-right")){
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==true){
            colision='t'; 
            rath->move(-1,-1);
        }
        if(rath->getHitbox()->checkCollision(enemy2->getHitbox())==false && colision!='t'){
            rath->move(1,1);
            colision='z';
        } 
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }
    if(!Game::Instance()->iM->isActive("player-up") && !Game::Instance()->iM->isActive("player-down") && 
        !Game::Instance()->iM->isActive("player-left") && !Game::Instance()->iM->isActive("player-right") && mov == true){
        rath->getAnimation()->changeAnimation("idle", false);
        mov=false;
        direcNow='i';
    }
    if(ata==true){
        rath->getAnimation()->queueAnimation("idle", false);
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        ata=false;
    }
}

void LevelState::Render(){
    
    sf::View view = sf::View(sf::FloatRect(0,0,1280,720));
    
    Game::Instance()->window->setView(view);
    
    rath->getAnimation()->updateAnimator();
    enemy2->getAnimation()->updateAnimator();
    
    Coordinate inc(rath->getState()->getIC());
    Coordinate inc2(enemy2->getState()->getIC());
    
    rath->setPosition(Coordinate(inc.x, inc.y));
    enemy2->setPosition(inc2.x, inc2.y);
    
    Game::Instance()->window->setView(Game::Instance()->view);
    
    level->drawAll();
    
    Game::Instance()->view.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
    Game::Instance()->window->draw(*enemy2->getAnimation()->getSprite());
    
    console->drawConsole();
}

void LevelState::CleanUp(){
    
}
