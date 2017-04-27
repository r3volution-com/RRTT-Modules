#include "Button.h"
#include "Game.h"

Button::Button(Coordinate pos, Texture *bL, Rect<float> textureRect) {
    buttonLayout = new Sprite(bL, textureRect);
    buttonLayout->setPosition(pos);
    buttonData = new Rect<float>(pos.x, pos.y, textureRect.w, textureRect.h);
    hitbox = new Hitbox(*buttonData);
    isHover = false;
}

Button::~Button() {
    delete text;
    delete hitbox;
    delete buttonLayout;
    delete buttonData;
    text = NULL;
    hitbox = NULL;
    buttonLayout = NULL;
    buttonData = NULL;
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

void Button::draw(){
    Game::Instance()->window->draw(*buttonLayout->getSprite());
    Game::Instance()->window->draw(*text->getText());
}
