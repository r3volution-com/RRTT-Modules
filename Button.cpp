#include "Button.h"

#include <iostream>

Button::Button(Coordinate pos, Texture *bL, Rect<float> textureRect) {
    buttonLayout = new Sprite(bL, textureRect);
    buttonLayout->setPosition(pos);
    buttonData = new Rect<float>(pos.x, pos.y, textureRect.w, textureRect.h);
    hitbox = new Hitbox(*buttonData);
    isHover = false;
}

Button::~Button() {
}

void Button::setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size){
    text = new Text(t, Coordinate(buttonData->x+(buttonData->w/2), buttonData->y), f, false);
    text->setStyles(color, outlineColor, 1, size);
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !isHover){
        buttonLayout->changeSpriteRect(Rect<float>(buttonLayout->getOriginalSpriteRect()->x+buttonData->w, buttonLayout->getOriginalSpriteRect()->y, buttonData->w, buttonData->h));

        isHover = true;
    } else if (!hitbox->checkCollision(mouse) && isHover){
        buttonLayout->changeSpriteRect(*buttonLayout->getOriginalSpriteRect());
        
        isHover = false;
    }
}

void Button::draw(sf::RenderWindow *window){
    window->draw(*buttonLayout->getSprite());
    window->draw(*text->getText());
}
