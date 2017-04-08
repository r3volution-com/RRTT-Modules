#include "IntroState.h"
#include "Game.h"

IntroState::IntroState() {
    rM = new ResourceManager();
    rM->loadTexture("background", "resources/background-intro.png");
    iM = new Event();
}

IntroState::~IntroState(){
    
}

void IntroState::Init(){
    background = new Sprite(rM->getTexture("background"), Rect<float>(0,0,Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    iM->addAction("skip", thor::Action(sf::Keyboard::Space));
    iM->addAction("close", thor::Action(sf::Keyboard::Escape, thor::Action::ReleaseOnce) || thor::Action(sf::Event::Closed));
}

void IntroState::Input(){
    if (iM->isActive("skip")) Game::Instance()->ChangeCurrentState("menu");
    if (iM->isActive("close")) Game::Instance()->window->close();
}

void IntroState::Update(){
    iM->update();
}

void IntroState::Render(){
    Game::Instance()->window->draw(*background->getSprite());
}

void IntroState::CleanUp(){
    
}