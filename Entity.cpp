#include "Entity.h"

Entity::Personaje() {
}

Entity::~Personaje() {
}

void Entity::loadSprite(Texture texture){
    
}

void Entity::move(float dirX, float dirY){
    
}

bool Entity::collision(Rect<float> other){
    return hitbox.intersects(other);
}

void Entity::die(){
    
}