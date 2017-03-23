#include "Animation.h"
#include "InterpolatedCoordinate.h"
#include "Rect.h"

/*
 * t = textura
 * tRect = rectangulo del Sprite
 * nS = numero de Sprites de la animacion
 * d = delay
 */
Animation::Animation(Texture *t, Rect *tRect, int nS, float d) {
    //Copiamos las variables
    tex = t;
    numSprites = nS;
    delay = d;
    currentSprite = 0;
    rectSprite = tRect;
    
    //CoordenadaIntepolada
    coordinate = new InterpolatedCoordinate(0,0);
    
    //Inicializo el timer
    clock = new sf::Clock();
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprites = new sf::Sprite(*tex->getTexture());
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprites->setTextureRect(rectSprite->getRect());

    //Le pongo el centroide donde corresponde
    sprites->setOrigin(0,0);

    //Y lo coloco provisionalmente
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

void Animation::setPosition(Coordinate *newCoord){
    sprites->setPosition(newCoord->x, newCoord->y);
}

void Animation::move(float x, float y){
    sprites->move(x, y);
}

void Animation::changeSpriteRect(Rect *newRect){
    rectSprite->x = newRect->x;
    rectSprite->y = newRect->y;
    rectSprite->w = newRect->w;
    rectSprite->h = newRect->h;
    sprites->setTextureRect(rectSprite->getRect());
}

void Animation::changeCurrentSprite(){
    if (clock->getElapsedTime().asSeconds() > delay){
        if (currentSprite < numSprites) currentSprite++;
        else currentSprite = 0;
        rectSprite->x = rectSprite->w*currentSprite;
        sprites->setTextureRect(rectSprite->getRect());
        clock->restart();
    }
}

sf::Sprite Animation::getCurrentSprite(){
    changeCurrentSprite();
    return *sprites;
}