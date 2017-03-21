#include "Animation.h"

/*
 * t = textura
 * w = ancho 
 * h = alto
 * cX = coordenada X del primer sprite
 * cY = coordenada Y del primer sprite
 * nS = numero de Sprites de la animacion
 * d = delay
 */
Animation::Animation(Texture *t, int w, int h, int cX, int cY, int nS, float d) {
    //Copiamos las variables
    tex = t;
    width = w;
    height = h;
    clipX = cX;
    clipY = cY;
    numSprites = nS;
    currentSprite = 0;
    delay = d;
    
    clock = new sf::Clock;
    
    //Creamos el cuadrado del sprite actual
    rectSprite = new sf::IntRect(cX, cY, w, h);
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprites = new sf::Sprite(*tex->getTexture());
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprites->setTextureRect(*rectSprite);

    //Le pongo el centroide donde corresponde
    sprites->setOrigin(0,0);

    //Y lo colocamos provisionalmente
    sprites->setPosition(0,0);
}

Animation::~Animation() {
    delete sprites;
    delete tex;
    delete clock;
    delete rectSprite;
    sprites = NULL;
    tex = NULL;
    clock = NULL;
    rectSprite = NULL;
}

void Animation::setPosition(float x, float y){
    sprites->setPosition(x, y);
}

void Animation::move(float x, float y){
    sprites->move(x, y);
}

void Animation::changeSpriteRect(int cX, int cY, int w, int h){
    rectSprite->left = cX;
    rectSprite->top = cY;
    rectSprite->width = w;
    rectSprite->height = h;
    sprites->setTextureRect(*rectSprite);
}

void Animation::changeCurrentSprite(){
    if (clock->getElapsedTime().asSeconds() > delay){
        if (currentSprite < numSprites) currentSprite++;
        else currentSprite = 0;
        rectSprite->left = width*currentSprite;
        sprites->setTextureRect(*rectSprite);
        clock->restart();
    }
}

sf::Sprite Animation::getCurrentSprite(){
    changeCurrentSprite();
    return *sprites;
}