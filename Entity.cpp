#include "Entity.h"

Entity::Entity(Coordinate position, Coordinate s, float sp) {
    speed = sp;
    
    size = new Coordinate(s);
    coor = new InterpolatedCoordinate(position.x, position.y);
    hitbox = new Hitbox(position.x, position.y, s.x, s.y);
    hitbox->setPosition(position);
    initial = new Coordinate(position.x, position.y);
}

Entity::~Entity() {
    delete coor;
    delete hitbox;
    delete anim;
    delete initial;
    delete size;
    coor = NULL;
    hitbox = NULL;
    anim = NULL;
    initial = NULL;
    size = NULL;
}

void Entity::setSprite(Texture *t, Rect<float> newRect){
    anim = new Animation(t, Rect<float>(newRect.x, newRect.y, newRect.w, newRect.h));
    anim->setPosition(*initial);
}

void Entity::move(float dirX, float dirY){
    coor->move(dirX*speed, dirY*speed);
}

void Entity::move(float dirX, float dirY, float sp){
    coor->move(dirX*sp, dirY*sp);
}

void Entity::setPosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
    if(hitbox->hitbox->height<anim->getSprite()->getLocalBounds().height){
       hitbox->setPosition(hitbox->hitbox->left, hitbox->hitbox->top +(anim->getSprite()->getLocalBounds().height - hitbox->hitbox->height));
    }
    if(hitbox->hitbox->width < anim->getSprite()->getLocalBounds().width){
        hitbox->setPosition(hitbox->hitbox->left + (anim->getSprite()->getLocalBounds().width-hitbox->hitbox->width)/2 , hitbox->hitbox->top);
    }
    //AJUSTAR HITBOX A EL DIBUJO
    coor->setCoordinate(newCoor);
}

void Entity::setPosition(float x, float y){
    anim->setPosition(x, y);
    hitbox->setPosition(x, y);
     if(hitbox->hitbox->height<anim->getSprite()->getLocalBounds().height){
       hitbox->setPosition(hitbox->hitbox->left, hitbox->hitbox->top +(anim->getSprite()->getLocalBounds().height - hitbox->hitbox->height));
    }
    if(hitbox->hitbox->width < anim->getSprite()->getLocalBounds().width){
        hitbox->setPosition(hitbox->hitbox->left + (anim->getSprite()->getLocalBounds().width - hitbox->hitbox->width)/2 , hitbox->hitbox->top);
    }
    coor->setCoordinate(x, y);
}

void Entity::updatePosition(Coordinate newCoor){
    anim->setPosition(newCoor);
    hitbox->setPosition(newCoor);
     if(hitbox->hitbox->height<anim->getSprite()->getLocalBounds().height){
       hitbox->setPosition(hitbox->hitbox->left, hitbox->hitbox->top +(anim->getSprite()->getLocalBounds().height - hitbox->hitbox->height));
    }
    if(hitbox->hitbox->width < anim->getSprite()->getLocalBounds().width){
        hitbox->setPosition(hitbox->hitbox->left + (anim->getSprite()->getLocalBounds().width - hitbox->hitbox->width)/2 , hitbox->hitbox->top);
    }
}

void Entity::updatePosition(float x, float y){
    anim->setPosition(x, y);
     if(hitbox->hitbox->height<anim->getSprite()->getLocalBounds().height){
       hitbox->setPosition(hitbox->hitbox->left, hitbox->hitbox->top +(anim->getSprite()->getLocalBounds().height - hitbox->hitbox->height));
    }
    hitbox->setPosition(x, y);if(hitbox->hitbox->width < anim->getSprite()->getLocalBounds().width){
        hitbox->setPosition(hitbox->hitbox->left + (anim->getSprite()->getLocalBounds().width - hitbox->hitbox->width)/2 , hitbox->hitbox->top);
    }
    
}
        
bool Entity::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}