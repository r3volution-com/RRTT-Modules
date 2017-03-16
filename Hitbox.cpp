#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, int w, int h) {
    hitbox = new sf::Rect<float>(x, y, w, h);
}

Hitbox::~Hitbox() {
    delete hitbox;
    hitbox = NULL;
}

void Hitbox::setPosition(float x, float y){
    hitbox->left = x;
    hitbox->top = y;
}

void Hitbox::move(float x, float y){
    hitbox->left = hitbox->left+x;
    hitbox->top = hitbox->top+y;
}

bool Hitbox::checkCollision(Hitbox *other){
    return hitbox->intersects(*other->hitbox);
}