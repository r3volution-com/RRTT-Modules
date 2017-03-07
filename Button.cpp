#include "Button.h"

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
}

Button::~Button() {
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !h){
        int cX = buttonLayout->getSpriteRect().left+bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        h = true;
    } else if (!hitbox->checkCollision(mouse) && h){
        int cX = buttonLayout->getSpriteRect().left-bW;
        int cY = buttonLayout->getSpriteRect().top;
        buttonLayout->changeSpriteRect(cX, cY, bW, bH);
        h = false;
    }
}

Sprite *Button::getSprite(){
    sf::RenderTexture *texture;
    texture->create(bW, bH);
    
    texture->draw(buttonLayout->getSprite());
    texture->draw(text->getText());
    Texture *t = new Texture(texture);
    Sprite *target = new Sprite(t, bW, bH, 0, 0);
    return target;
}