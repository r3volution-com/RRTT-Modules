#include "LevelState.h"
#include "Game.h"

#define PI 3,14159265f;

LevelState::LevelState() : GameState(){
    
}

LevelState::~LevelState(){
    
}

void LevelState::Init(){
    Game::Instance()->rM->loadTexture("player", "resources/sprites.png");
    rath = new Player(Coordinate(0,0), Game::Instance()->rM->getTexture("player"), Rect<float>(0,0, 128, 128), 10);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
    Game::Instance()->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    Game::Instance()->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    Game::Instance()->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    Game::Instance()->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    Game::Instance()->iM->addAction("player-Lclick", thor::Action(sf::Mouse::Left));
    
    Game::Instance()->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    Game::Instance()->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    Game::Instance()->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    Game::Instance()->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
}

void LevelState::Update(){
}

void LevelState::Input(){
    /*if (Game::Instance()->iM->isActive("player-up")){ 
        rath->move(0,-1);
        if(direcNow!='u'){
                rath->getAnimation()->changeAnimation("correrArriba", false);
            }
            direcNow='u';
            mov=true;
    }
    if (Game::Instance()->iM->isActive("player-down")){ 
        rath->move(0,1);
        if(direcX=='r' && direcNow!='d'){
         rath->getAnimation()->changeAnimation("correrDerecha", false);  
                mov=true;
                direcNow='d';
                }
            else{
                if(direcX=='l' && direcNow!='l'){
                    rath->getAnimation()->changeAnimation("correrIzquierda", false);
                    mov=true;
                    direcNow='d';
                }
            }
    }
    if (Game::Instance()->iM->isActive("player-left")){
        rath->move(-1,0);
                if(direcNow!='l'){
                    rath->getAnimation()->changeAnimation("correrIzquierda", false);
                }
                direcX='l';
                direcNow='l';
                mov=true;
    }
    if (Game::Instance()->iM->isActive("player-right")){
        rath->move(1,0);
        if(direcNow!='r'){
                rath->getAnimation()->changeAnimation("correrDerecha", false);
            }
            direcX='r';
            direcNow='r';
            mov=true;
    }
    if (Game::Instance()->iM->isActive("player-Lclick")){
        
    }
    */
    
    /*if (Game::Instance()->iM->isActive("player-up") && Game::Instance()->iM->isActive("player-left")) rath->move(-1,-1);
    if (Game::Instance()->iM->isActive("player-up") && Game::Instance()->iM->isActive("player-right")) rath->move(1,-1);
    if (Game::Instance()->iM->isActive("player-down") && Game::Instance()->iM->isActive("player-left")) rath->move(-1,1);
    if (Game::Instance()->iM->isActive("player-down") && Game::Instance()->iM->isActive("player-right")) rath->move(1,1);*/
    if(Game::Instance()->iM->isActive("player-up-left")) rath->move(-1,-1);
    if(Game::Instance()->iM->isActive("player-up-right")) rath->move(1,-1);
    if(Game::Instance()->iM->isActive("player-down-left")) rath->move(-1,1);
    if(Game::Instance()->iM->isActive("player-down-right")) rath->move(1,1);
}

void LevelState::Render(){
    Coordinate inc(rath->getState()->getIC());
    //cout << inc;
    rath->getAnimation()->updateAnimator();
    rath->setPosition(inc.x, inc.y);
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
}

void LevelState::CleanUp(){
    
}