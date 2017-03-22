#include "Hitbox.h"
#include "Rect.h"
#include "Coordinate.h"

Hitbox::Hitbox(float x, float y, int w, int h) {
    hitbox = new sf::Rect<float>(x, y, w, h);
}

Hitbox::Hitbox(Rect *nRect){
    hitbox = new sf::Rect<float>(nRect->x, nRect->y, nRect->w, nRect->h);
}

Hitbox::~Hitbox() {
    delete hitbox;
    hitbox = NULL;
}

void Hitbox::setPosition(float x, float y){
    hitbox->left = x;
    hitbox->top = y;
}

void Hitbox::setPosition(Coordinate *newCoor){
    hitbox->left = newCoor->x;
    hitbox->top = newCoor->y;
}

void Hitbox::move(float x, float y){
    hitbox->left = hitbox->left+x;
    hitbox->top = hitbox->top+y;
}

bool Hitbox::checkCollision(Hitbox *other){
    return hitbox->intersects(*other->hitbox);
}