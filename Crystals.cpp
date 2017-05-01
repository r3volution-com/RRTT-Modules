#include "Crystals.h"
#include <iostream>

Crystals::Crystals(Texture *tex, Rect<float> rect) {
    hitbox = new Hitbox(0, 0, rect.w, rect.h);
    
    sprite = new Sprite(tex, rect);
    touched = false;
}

Crystals::~Crystals() {
    delete hitbox;
    delete sprite;
    hitbox = NULL;
    sprite = NULL;
}

void Crystals::setPosition(Coordinate pos){
    sprite->setPosition(pos);
    hitbox->setPosition(pos);
}

void Crystals::setTouched(){
    touched = true;
}

bool Crystals::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}