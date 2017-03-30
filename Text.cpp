#include "Text.h"

Text::Text(std::string t, Coordinate position, Font* f, bool cO) {
    font = f;
    centerOrigin = cO;
    text = new sf::Text();
    text->setFont(*font->getFont());
    text->setString(t);
    text->setPosition(position.x, position.y);
    if (centerOrigin){
        sf::FloatRect textRect = text->getLocalBounds();
        text->setOrigin(textRect.width/2.0f, textRect.height/2.0f);
    }
}

Text::~Text() {
    delete font; //ToDo mario: creo que font no debe vaciarse aqui
    delete text;
    font = NULL;
    text = NULL;
}

void Text::setText(std::string t){
    text->setString(t);
    if (centerOrigin){
        sf::FloatRect textRect = text->getLocalBounds();
        text->setOrigin(textRect.width/2.0f, textRect.height/2.0f);
    }
}

void Text::setStyles(sf::Color color, sf::Color outlineColor, int outlineThickness, int size){
    text->setFillColor(color);
    text->setOutlineColor(outlineColor);
    text->setOutlineThickness(outlineThickness);
    text->setCharacterSize(size);
}

sf::Text *Text::getText() {
    return text;
}