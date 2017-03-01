#include "Personaje.h"

Personaje::Personaje() {
}

Personaje::~Personaje() {
}

void Personaje::loadSprite(Texture texture){
    
}

void Personaje::move(float dirX, float dirY){
    
}

bool Personaje::collision(Rect<float> other){
    return hitbox.intersects(other);
}

void Personaje::die(){
    
}