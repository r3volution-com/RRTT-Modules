#include "Button.h"

#include <iostream>

Button::Button(Coordinate *pos, Texture *bL, Rect<float> *textureRect) {
    buttonData = new Rect<float>(pos->x, pos->y, textureRect->w, textureRect->h);
    buttonLayout = new Sprite(bL, textureRect);
    hitbox = new Hitbox(buttonData);
    isHover = false;
    buttonLayout->setPosition(pos);
}

Button::~Button() {
}

void Button::setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size){
    text = new Text(t, new Coordinate(buttonData->x+(buttonData->w), buttonData->y+(buttonData->h)), f, true);
    text->setStyles(color, outlineColor, 1, size);
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !isHover){
        int cX = buttonLayout->getActualSpriteRect()->x+buttonData->w;
        int cY = buttonLayout->getActualSpriteRect()->y;
        buttonLayout->changeSpriteRect(new Rect<float>(cX, cY, buttonData->w, buttonData->h));
        
        isHover = true;
    } else if (!hitbox->checkCollision(mouse) && isHover){
        int cX = buttonLayout->getActualSpriteRect()->x-buttonData->w;
        int cY = buttonLayout->getActualSpriteRect()->y;
        buttonLayout->changeSpriteRect(new Rect<float>(cX, cY, buttonData->w, buttonData->h));
        
        isHover = false;
    }
}

void Button::draw(sf::RenderWindow *window){
    window->draw(buttonLayout->getSprite());
    window->draw(*text->getText());
}
