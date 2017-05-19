#include "Crystal.h"
#include <iostream>

Crystal::Crystal(Texture *tex, Rect<float> rect) {
    hitbox = new Hitbox(0, 0, rect.w, rect.h);
    
    sprite = new Sprite(tex, rect);
    touched = false;
}

Crystal::~Crystal() {
    delete hitbox;
    delete sprite;
    hitbox = NULL;
    sprite = NULL;
}

void Crystal::setPosition(Coordinate pos){
    sprite->setPosition(pos);
    hitbox->setPosition(pos);
}

void Crystal::setTouched(){
    touched = true;
}

bool Crystal::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}