#include "IntroState.h"
#include "Game.h"

IntroState::IntroState() {
    
}

IntroState::~IntroState(){
    delete background;
    background = NULL;
}

void IntroState::Init(){
    Game::Instance()->rM->loadTexture("background", "resources/background-intro.png");
    background = new Sprite(Game::Instance()->rM->getTexture("background"), Rect<float>(0,0,Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    
    Game::Instance()->iM->addAction("skip-intro", thor::Action(sf::Keyboard::Space));
}

void IntroState::Input(){
    if (Game::Instance()->iM->isActive("skip-intro")) Game::Instance()->ChangeCurrentState("menu");
}

void IntroState::Update(){
    
}

void IntroState::Render(){
    Game::Instance()->window->draw(*background->getSprite());
}

void IntroState::CleanUp(){
    Game::Instance()->rM->releaseTexture("background");
    delete background;
}