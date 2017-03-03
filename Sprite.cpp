#include "Sprite.h"

Sprite::Sprite(Texture *texture, int w, int h, int cX, int cY) {
    //Copiamos las variables
    tex = texture;
    maxW = w;
    maxH = h;
    clipX = cX;
    clipY = cY;
    
    spriteRect = new sf::IntRect(clipX, clipY, w, h);
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = new sf::Sprite(*tex->getTexture());
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprite->setTextureRect(*spriteRect);
    
    //Le pongo el centroide donde corresponde
    sprite->setOrigin(0,0);
    
    //Y lo colocamos provisionalmente
    sprite->setPosition(0,0);
}

Sprite::~Sprite() {
    delete tex;
    delete sprite;
    delete spriteRect;
    tex = NULL;
    sprite = NULL;
    spriteRect = NULL;
}

void Sprite::move(float x, float y){
    sprite->move(x, y);
}

void Sprite::setSize(int w, int h){
    spriteRect->width = w;
    spriteRect->height = h;
    sprite->setTextureRect(*spriteRect);
}

void Sprite::changeSpriteRect(int cX, int cY, int w, int h){
    spriteRect->left = cX;
    spriteRect->top = cY;
    spriteRect->width = w;
    spriteRect->height = h;
    sprite->setTextureRect(*spriteRect);
}

void Sprite::restoreSize(){
    spriteRect->left = clipX;
    spriteRect->top = clipY;
    spriteRect->width = maxW;
    spriteRect->height = maxH;
    sprite->setTextureRect(*spriteRect);
}