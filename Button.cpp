#include "Button.h"

#include <iostream>

Button::Button(Coordinate *pos, Texture *bL, Rect *textureRect) {
    buttonData = new Rect(pos->x, pos->y, textureRect->w, textureRect->h);
    buttonLayout = new Sprite(bL, textureRect);
    hitbox = new Hitbox(buttonData);
    isHover = false;
    buttonLayout->setPosition(pos->x, pos->y);
}

Button::~Button() {
}

void Button::setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size){
    text = new Text(t, buttonData->x+(buttonData->w/2), buttonData->y+(buttonData->h), f, true);
    text->setStyles(color, outlineColor, 1, size);
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !isHover){
        int cX = buttonLayout->getSpriteRect().left+rect->w;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, rect->w, rect->h);
        
        isHover = true;
    } else if (!hitbox->checkCollision(mouse) && isHover){
        int cX = buttonLayout->getSpriteRect().left-rect->w;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, rect->w, rect->h);
        
        isHover = false;
    }
}

void Button::draw(sf::RenderWindow *window){
    window->draw(buttonLayout->getSprite());
    window->draw(*text->getText());
}