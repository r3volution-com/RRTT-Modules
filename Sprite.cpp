#include "Sprite.h"
#include "Coordinate.h"
#include "Rect.h"

Sprite::Sprite(Texture *texture, Rect *spriteRect) {
    //Copiamos las variables
    tex = texture;
    
    originalSpriteRect = new Rect(spriteRect->getRect());
    actualSpriteRect = new Rect(spriteRect->getRect());
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = new sf::Sprite(*tex->getTexture());
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprite->setTextureRect(actualSpriteRect->getRect());
    
    //Le pongo el centroide donde corresponde
    sprite->setOrigin(0,0);
    
    //Y lo colocamos provisionalmente
    sprite->setPosition(0,0);
}

Sprite::~Sprite() {
    delete tex;
    delete sprite;
    tex = NULL;
    sprite = NULL;
}

void Sprite::move(float x, float y){
    sprite->move(x, y);
}

void Sprite::setPosition(Coordinate *pos){
    sprite->setPosition(pos->x, pos->y);
}

void Sprite::setSize(float w, float h){
    actualSpriteRect->w = w;
    actualSpriteRect->h = h;
    sprite->setTextureRect(actualSpriteRect->getRect());
}

void Sprite::changeSpriteRect(Rect *spriteRect){
    actualSpriteRect->setRect(spriteRect->getRect());
    sprite->setTextureRect(actualSpriteRect->getRect());
}

void Sprite::restoreSize(){
    actualSpriteRect->setRect(originalSpriteRect->getRect());
    sprite->setTextureRect(actualSpriteRect->getRect());
}

Coordinate Sprite::getPosition(){
    return Coordinate(sprite->getPosition().x, sprite->getPosition().y);
}