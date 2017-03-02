#include "Entity.h"

Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::loadAnimation(Texture *t, int w, int h, int cX, int cY, int nS, float d){
    anim = new Animation(t->getTexture(), w, h, cX, cY, nS, d);
}

void Entity::move(float dirX, float dirY){
    anim->move(dirX*speed, dirY*speed);
}

/*bool Entity::collision(Hitbox other){
    return hitbox.intersects(other);
}*/