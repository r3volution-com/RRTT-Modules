#include "LevelState.h"

LevelState::LevelState(){
    
     hud = new HUD();
     
}

LevelState::Render(){
    
}

LevelState::Update(){
    
}

LevelState::Input(){
    
}

LevelState::Pause(){
    
}

LevelState::Resume(){
    
}

LevelState::CleanUp(){
    
}

void LevelState::populate(std::vector<sf::RectangleShape*> *objects, float x, float y)
{
    sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(20, 20));
    s->setPosition(x, y);
    s->setFillColor(sf::Color::Green);
    objects->push_back(s);
}
