#include "Crystal.h"
#include <iostream>

Crystal::Crystal(Texture *tex, Rect<float> rect, Texture *sparksTexture, Rect<float> sparksRect) {
    hitbox = new Hitbox(0, 0, rect.w, rect.h);
    
    anim = new Animation(tex, rect);
    sparks = new Particles(sparksTexture);
    sparks->addParticle(sparksRect);
    touched = false;
}

Crystal::~Crystal() {
    delete hitbox;
    delete anim;
    delete sparks;
    sparks = NULL;
    hitbox = NULL;
    anim = NULL;
}

void Crystal::setPosition(Coordinate pos){
    anim->setPosition(pos);
    hitbox->setPosition(pos);
}

void Crystal::setTouched(){
    touched = true;
}

bool Crystal::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}