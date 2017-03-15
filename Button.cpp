#include "Button.h"

#include <iostream>

Button::Button(std::string t, float x, float y, int w, int h, Sprite *bL) {
    text = new Text(t, x+(w/2), y+(h/2));
    bX = x;
    bY = y;
    bW = w;
    bH = h;
    buttonLayout = bL;
    hitbox = new Hitbox(x, y, w, h);
    h = false;
    bL->move(x, y);
    tButton = new Texture(tButton->createRenderTexture(bW, bH));
    tButton->getRenderTexture()->draw(buttonLayout->getSprite());
    tButton->getRenderTexture()->draw(text->getText());
    
    button = new Sprite(tButton, bW, bH, 0, 0);
}

Button::~Button() {
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !h){
        int cX = buttonLayout->getSpriteRect().left+bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        
        tButton->getRenderTexture()->clear();
        tButton->getRenderTexture()->draw(buttonLayout->getSprite());
        tButton->getRenderTexture()->draw(text->getText());
        delete button;
        button = new Sprite(tButton, bW, bH, 0, 0);
        
        h = true;
    } else if (!hitbox->checkCollision(mouse) && h){
        int cX = buttonLayout->getSpriteRect().left-bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        
        tButton->getRenderTexture()->clear();
        tButton->getRenderTexture()->draw(buttonLayout->getSprite());
        tButton->getRenderTexture()->draw(text->getText());
        delete button;
        button = new Sprite(tButton, bW, bH, 0, 0);
        
        h = false;
    }
}

Sprite *Button::getSprite(){
    return button;
}