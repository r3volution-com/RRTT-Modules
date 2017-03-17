#include "Button.h"

#include <iostream>

Button::Button(float x, float y, int w, int h, Sprite *bL) {
    bX = x;
    bY = y;
    bW = w;
    bH = h;
    buttonLayout = bL;
    hitbox = new Hitbox(x, y, w, h);
    ho = false;
    buttonLayout->setPosition(x,y);
}

Button::~Button() {
}

void Button::setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size){
    text = new Text(t, bX+(bW/2), bY+(bH), f, true);
    text->setStyles(color, outlineColor, 1, size);
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !ho){
        int cX = buttonLayout->getSpriteRect().left+bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        
        ho = true;
    } else if (!hitbox->checkCollision(mouse) && ho){
        int cX = buttonLayout->getSpriteRect().left-bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        
        ho = false;
    }
}

void Button::draw(sf::RenderWindow *window){
    window->draw(buttonLayout->getSprite());
    window->draw(*text->getText());
}