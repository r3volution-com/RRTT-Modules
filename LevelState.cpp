#include "LevelState.h"
#include "Game.h"

LevelState::LevelState() : GameState(){
    rM = new ResourceManager();
    rM->loadTexture("player", "resources/sprites.png");
    playerTexture = rM->getTexture("player");
    rath = new Player(Coordinate(0,0), playerTexture, Rect<float>(0,0, 128, 128), 2);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
}

LevelState::~LevelState(){
    
}

void LevelState::Init(){
    
}

void LevelState::Update(){
    rath->getAnimation()->updateAnimator();
}

void LevelState::Input(){
    
}

void LevelState::Render(){
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
}

void LevelState::CleanUp(){
    
}