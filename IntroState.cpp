#include "IntroState.h"
#include "Game.h"

IntroState::IntroState() {
    rM = new ResourceManager();
    rM->loadTexture("player", "resources/sprites.png");
    playerTexture = rM->getTexture("player");
    rath = new Player(Coordinate(0,0), playerTexture, Rect<float>(0,0, 128, 128), 2);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
}

void IntroState::CleanUp(){
    
}

void IntroState::Input(){
    std::cout << "ye";
}

void IntroState::Pause(){
    
}

void IntroState::Render(){
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    
}

void IntroState::Resume(){
    
}

void IntroState::Update(){
    rath->getAnimation()->updateAnimator();
}

IntroState::~IntroState(){
    
}