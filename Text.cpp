#include "Text.h"
#include <sstream>

Text::Text(std::string t, float x, float y, sf::Color color, Font* f, int size) { //ToDo: esto se puede hacer mejor cuando tengamos el singleton
    font = f;
    text = new sf::Text();
    text->setFont(*font->getFont());
    text->setString(t);
    text->setPosition(x, y);
    text->setFillColor(color);
    text->setCharacterSize(size);
    sf::FloatRect textRect = text->getLocalBounds();
    text->setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
}

Text::~Text() {
}

sf::Text *Text::getText() {
    return text;
}