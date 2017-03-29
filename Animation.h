#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Coordinate.h"
#include "Texture.h"
#include "InterpolatedCoordinate.h"
#include "Rect.h"

class Animation {
    private:
        Texture *tex;
        Rect<float> *rectSprite;
        InterpolatedCoordinate *coordinate;
        Coordinate *clipCoordinate;
        sf::Sprite *sprites;
        sf::Clock *clock;
        float delay;
        int currentSprite;
        int numSprites;
        
        void changeCurrentSprite();
    public:
        /**
         * Creación de una animación
         * @param t: Puntero a textura
         * @param tRect: Puntero a zona a mostrar de la textura
         * @param nS: Numero de sprites
         * @param d: Druacion de la animacion
         */
        Animation(Texture *t, Rect<float> *tRect, int nS, float d);
        virtual ~Animation();
        
        /**
         * Actualiza la posicion de la animacion
         * @param x: Coordenada x de la posicion
         * @param y: Coordenada y de la posicion
         */
        void setPosition(float x, float y);
        /**
         * Actualiza la posicion de la animacion
         * @param newCoord: Puntero a cooordenadas de la animación
         */
        void setPosition(Coordinate *newCoord);
        /**
         * Actualiza la rotacion de la animacion
         * @param r: Grados a rotar
         */
        void setRotation(float r);
        /**
         * Actualiza el origen en el que empieza la animacion
         * @param x: Coordenada x para el origen
         * @param y: Coordenada y para el origen
         */
        void setOrigin(float x, float y);
        
        /**
         * Movimiento de la animacion
         * @param x: movimiento en el eje x
         * @param y: movimiento en el eje y
         */
        void move(float x, float y);
        /**
         * Cambio en la zona de representacion del sprite
         * @param newRect
         */
        void changeSpriteRect(Rect<float> *newRect);
        
        sf::Sprite getCurrentSprite();
};

#endif /* ANIMATION_H */
