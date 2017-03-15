#include "Text.h"

Text::Text(std::string t, float x, float y, sf::Color color, Font* f) {
    font = f;
    text = new sf::Text();
    text->setFont(font->getFont());
    text->setString(t);
    text->setPosition(x, y);
    text->setFillColor(color);
    //ToDo: centrar texto
    
}

Text::~Text() {
}