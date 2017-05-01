#include "LevelState.h"
#include "Game.h"
#include "Level.h"
#include "Console.h"

#define PI 3,14159265f;

LevelState::LevelState() : GameState(){
    
}

LevelState::~LevelState(){
    
}

void LevelState::Init(){
    level = new Level(1);
    
    Game *game = Game::Instance();
    
    game->rM->loadTexture("player", "resources/sprites.png");
    game->rM->loadTexture("console-bg", "resources/console-bg.png");
    game->rM->loadFont("console", "resources/font.ttf");
    
    rath = new Player(Coordinate(3900,2700), game->rM->getTexture("player"), Rect<float>(0,0, 128, 128), 15);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
    
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

}

void LevelState::Update(){
    
    level->enemyAI(rath);
    
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
        
    }*/
    
    if(Game::Instance()->iM->isActive("player-up-left")) rath->move(-1,-1);
    if(Game::Instance()->iM->isActive("player-up-right")) rath->move(1,-1);
    if(Game::Instance()->iM->isActive("player-down-left")) rath->move(-1,1);
    if(Game::Instance()->iM->isActive("player-down-right")) rath->move(1,1);
    
    if(Game::Instance()->iM->isActive("console")) console->toggleActive();
}

void LevelState::Render(){
    Game::Instance()->window->setView(Game::Instance()->view);
    
    level->drawAll();
    
    Coordinate inc(rath->getState()->getIC());
    //cout << inc;
    rath->getAnimation()->updateAnimator();
    rath->setPosition(inc.x, inc.y);
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    console->drawConsole();
}

void LevelState::CleanUp(){
    
}