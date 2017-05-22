#include "Crystal.h"
#include <iostream>

Crystal::Crystal(Texture *tex, Rect<float> rect, Texture *sparksTexture, Rect<float> sparksRect) {
    hitbox = new Hitbox(0, 0, rect.w, rect.h);
    
    anim = new Animation(tex, rect);
    sparks = new Particles(sparksTexture);
    sparks->addParticle(sparksRect);
    sparks->setProperties(10,0.1f,0.5f);
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

void Crystal::startSparks(){
    sparks->setParticlePosition(thor::Distributions::circle(sf::Vector2f(hitbox->hitbox->left+(hitbox->hitbox->width/2), hitbox->hitbox->top+(hitbox->hitbox->height/2)), 30));
    sparks->start();
}

void Crystal::drawSparks(){
    sparks->update();
    sparks->draw();
}