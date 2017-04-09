#include "LevelState.h"
#include "Game.h"

LevelState::LevelState() : GameState(){
    
}

LevelState::~LevelState(){
    
}

void LevelState::Init(){
    Game::Instance()->rM->loadTexture("player", "resources/sprites.png");
    rath = new Player(Coordinate(0,0), Game::Instance()->rM->getTexture("player"), Rect<float>(0,0, 128, 128), 15);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
    Game::Instance()->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    Game::Instance()->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    Game::Instance()->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    Game::Instance()->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
}

void LevelState::Update(){
    rath->getAnimation()->updateAnimator();
}

void LevelState::Input(){
    if (Game::Instance()->iM->isActive("player-up")) rath->move(0,-1);
    if (Game::Instance()->iM->isActive("player-down")) rath->move(0,1);
    if (Game::Instance()->iM->isActive("player-left")) rath->move(-1,0);
    if (Game::Instance()->iM->isActive("player-right")) rath->move(1,0);
}

void LevelState::Render(){
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
}

void LevelState::CleanUp(){
    
}