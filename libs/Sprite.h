#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Coordinate.h"
#include "Rect.h"

class Sprite {
    private:
        Texture *tex;
        sf::Sprite *sprite;
        Rect<float> *actualSpriteRect;
        Rect<float> *originalSpriteRect;
    public:
        /**
         * Creacion de un sprite
         * @param texture: Textrua del sprite
         * @param spriteRect: Zona a imprimir del sprite
         */
        Sprite(Texture *texture, Rect<float> spriteRect);
        virtual ~Sprite();
        
        /**
         * Establece la posicion del sprite
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setPosition(float x, float y);
        
        /**
         * Establece la posicion del sprite
         * @param pos: Tipo Coordinate, coordenadas
         */
        void setPosition(Coordinate pos);
        
        /**
         * Establece la rotacion del sprite
         * @param r: radio
         */
        void setRotation(float r);
        
        /**
         * Establece el tamaño del sprite
         * @param w: Ancho
         * @param h: Alto
         */
        void setSize(float w, float h);
        
        /**
         * Cambio de zona de impresion del sprite
         * @param spriteRect: Zona de impresion del sprite
         */
        void changeSpriteRect(Rect<float> spriteRect);
        
        /**
         * Hacer que retome su tamaño
         */
        void restoreSize();
        
        Coordinate getPosition();
        sf::Sprite *getSprite() { return sprite; }
        Rect<float> *getActualSpriteRect() { return actualSpriteRect; }
        Rect<float> *getOriginalSpriteRect() { return originalSpriteRect; }
};

#endif /* SPRITE_H */
