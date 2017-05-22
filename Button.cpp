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
    delete outlineColor;
    delete outlineColorHover;
    text = NULL;
    hitbox = NULL;
    buttonLayout = NULL;
    buttonData = NULL;
    outlineColor = NULL;
    outlineColorHover = NULL;
}

void Button::setText(std::string t, sf::Color color, Font *f, int size){
    text = new Text(t, Coordinate(buttonData->x+(buttonData->w/2), buttonData->y+(buttonData->h/2)), f, true);
    text->setTextStyle(color, size);
    
}

void Button::setOutline(int oS, sf::Color oC, sf::Color oCH){
    outlineSize = oS;
    outlineColor = new sf::Color(oC);
    outlineColorHover = new sf::Color(oCH);
}

void Button::hover(Hitbox *mouse){
    if (hitbox->checkCollision(mouse) && !isHover){
        Game::Instance()->rM->getSound("menu")->getSound()->play();
        buttonLayout->changeSpriteRect(Rect<float>(buttonLayout->getOriginalSpriteRect()->x+buttonData->w, buttonLayout->getOriginalSpriteRect()->y, buttonData->w, buttonData->h));
        text->setOutlineStyle(*outlineColor, outlineSize);
        isHover = true;
    } else if (!hitbox->checkCollision(mouse) && isHover){
        buttonLayout->changeSpriteRect(*buttonLayout->getOriginalSpriteRect());
        text->setOutlineStyle(*outlineColorHover, outlineSize);
        isHover = false;
    }
}

void Button::draw(){
    Game::Instance()->window->draw(*buttonLayout->getSprite());
    Game::Instance()->window->draw(*text->getText());
}
