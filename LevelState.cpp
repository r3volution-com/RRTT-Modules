#include "LevelState.h"

LevelState::LevelState() : GameState(){
     
}

void LevelState::Render(){
    
}

void LevelState::Update(){
    
}

void LevelState::Input(){
    
}

void LevelState::Pause(){
    
}

void LevelState::Resume(){
    
}

void LevelState::CleanUp(){
    
}

void LevelState::populate(std::vector<sf::RectangleShape*> *objects, float x, float y)
{
    sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(20, 20));
    s->setPosition(x, y);
    s->setFillColor(sf::Color::Green);
    objects->push_back(s);
}

LevelState::~LevelState(){
    
}
