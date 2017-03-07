#include "Text.h"

Text::Text(std::string t, float x, float y) {
    text = new sf::Text;
    text->setString(t);
    text->setPosition(x, y);
    //ToDo: centrar texto
    
}

Text::~Text() {
}