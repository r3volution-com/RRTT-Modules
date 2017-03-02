#include "Sprite.h"

Sprite::Sprite(sf::Texture *texture, int w, int h, int cX, int cY) {
    //Copiamos las variables
    tex = texture;
    maxW = w;
    maxH = h;
    clipX = cX;
    clipY = cY;
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = *sf::Sprite(tex);
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprite->setTextureRect(sf::IntRect(clipX, clipY, w, h));
    
    //Le pongo el centroide donde corresponde
    sprite->setOrigin(0,0);
    
    //Y lo colocamos provisionalmente
    sprite->setPosition(0,0);
}

Sprite::~Sprite() {
    
}

void Sprite::move(float x, float y){
    sprite->move(x, y);
}

void Sprite::setSize(int w, int h){
    sprite->setTextureRect(sf::IntRect(clipX, clipY, w, h));
}

void Sprite::restoreSize(){
    sprite->setTextureRect(sf::IntRect(clipX, clipY, maxW, maxH));
}