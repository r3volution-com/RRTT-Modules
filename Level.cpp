#include "Level.h"

Level::Level(){
    
}

void Level::populate(std::vector<sf::RectangleShape*> *objects, float x, float y)
{
    sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(20, 20));
    s->setPosition(x, y);
    s->setFillColor(sf::Color::Green);
    objects->push_back(s);
}