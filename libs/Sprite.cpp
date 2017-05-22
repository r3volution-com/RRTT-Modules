#include "Sprite.h"

Sprite::Sprite(Texture *texture, Rect<float> spriteRect) {
    //Copiamos las variables
    tex = texture;
    
    originalSpriteRect = new Rect<float>(spriteRect.getRect());
    actualSpriteRect = new Rect<float>(spriteRect.getRect());
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = new sf::Sprite(*tex->getTexture());
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprite->setTextureRect(actualSpriteRect->getIntRect());
    
    //Le pongo el centroide donde corresponde
    sprite->setOrigin(0,0);
    
    //Y lo colocamos provisionalmente
    sprite->setPosition(0,0);
}

Sprite::~Sprite() {
    delete sprite;
    delete originalSpriteRect;
    delete actualSpriteRect;

    sprite = NULL;
    originalSpriteRect = NULL;
    actualSpriteRect = NULL;
}

void Sprite::setPosition(float x, float y){
    sprite->setPosition(x, y);
}

void Sprite::setPosition(Coordinate pos){
    sprite->setPosition(pos.x, pos.y);
}

void Sprite::setRotation(float r){
    sprite->setRotation(r);
}

void Sprite::setSize(float w, float h){
    actualSpriteRect->w = w;
    actualSpriteRect->h = h;
    sprite->setTextureRect(actualSpriteRect->getIntRect());
}

void Sprite::changeSpriteRect(Rect<float> spriteRect){
    actualSpriteRect->setRect(spriteRect.getRect());
    sprite->setTextureRect(actualSpriteRect->getIntRect());
}

void Sprite::restoreSize(){
    actualSpriteRect->setRect(originalSpriteRect->getRect());
    sprite->setTextureRect(actualSpriteRect->getIntRect());
}

Coordinate Sprite::getPosition(){
    return Coordinate(sprite->getPosition().x, sprite->getPosition().y);
}
