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
        text->setPosition(position.x+(textRect.width/6), position.y);
    }
}

Text::~Text() {
    //if(text != NULL) delete text;

    //text = NULL;
}

void Text::setText(std::string t){
    text->setString(t);
    if (centerOrigin){
        sf::FloatRect textRect = text->getLocalBounds();
        text->setOrigin(textRect.width/2.0f, textRect.height/2.0f);
    }
}

void Text::setTextStyle(sf::Color color, int size){
    text->setFillColor(color);
    text->setCharacterSize(size);
}

void Text::setOutlineStyle(sf::Color outlineColor, int outlineThickness){
    text->setOutlineColor(outlineColor);
    text->setOutlineThickness(outlineThickness);
}

sf::Text *Text::getText() {
    return text;
}
