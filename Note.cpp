#include "Note.h"
#include <iostream>

Note::Note(Texture *nTex, Rect<float> nRect, Texture *bTex, Rect<float> bRect, Font *f) {
    hitbox = new Hitbox(0, 0, nRect.w, nRect.h);
    
    noteSprite = new Sprite(nTex, nRect);
    backgroundSprite = new Sprite (bTex, bRect);
    text = new Text(std::string(), Coordinate(0, 0), f, true);
    taken = false;
}

Note::~Note() {
    
}

void Note::setPosition(Coordinate pos){
    noteSprite->setPosition(pos);
    hitbox->setPosition(pos);
}

void Note::setBackgroundPosition(Coordinate pos){
    backgroundSprite->setPosition(pos);
    text->setPosition(Coordinate(pos.x+(backgroundSprite->getActualSpriteRect()->w/2), pos.y+(backgroundSprite->getActualSpriteRect()->h/2)));
}

void Note::setText(std::string str, sf::Color color, sf::Color outlineColor, int outlineSize, int size){
    text->setText(str);
    text->setStyles(color, outlineColor, outlineSize, size);
}

void Note::setTaken(){
    taken = true;
}

bool Note::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}
