#ifndef ANIMATION_H
#define ANIMATION_H

#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>
#include "Coordinate.h"
#include "Rect.h"
#include "Texture.h"

class Animation {
    private:
        Texture *tex;
        Rect<float> *spriteRect;
        
        sf::Sprite *sprite;
        sf::Clock *clock;
        
        thor::AnimationMap<sf::Sprite, std::string> *animations;
        thor::Animator<sf::Sprite, std::string> *animator;
    public:
        /**
         * Creacion del objeto animacion
         * @param t: textura de la animacion
         * @param tRect: Zona a mostrar de la textura de la animacion
         */
        Animation(Texture *t, Rect<float> tRect);
        virtual ~Animation();
        
        /**
         * Adicion de una animacion
         * @param name: nombre de la animacion
         * @param clipCoord: coordenadas
         * @param nSprites: numero de sprites
         * @param duration: duracion de la animacion
         */
        void addAnimation(std::string name, Coordinate clipCoord, int nSprites, float duration);
        
        /**
         * Cambio de animacion
         * @param name: nombre de la animacion
         * @param loop: tipo bool bucle
         */
        void changeAnimation(std::string name, bool oneTime);
        
        /**
         * Animacion en cola
         * @param name: nombre de la animacion 
         * @param loop: tipo bool bucle
         */
        void queueAnimation(std::string name, bool oneTime);
        
        void initAnimator();
        void updateAnimator();
        
        /**
         * Establece la posicion de origen
         * @param newCoord: tipo Coordinate, coordenadas
         */
        void setOrigin(Coordinate newCoord);
        
        /**
         * Establece la posicion
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setPosition(float x, float y);
        
        /**
         * Establece la posicion
         * @param newCoord: Tipo Coordinate, coordenadas 
         */
        void setPosition(Coordinate newCoord);
        
        /**
         * Establece la rotacion
         * @param r: radio;
         */
        void setRotation(float r);
        
        sf::Sprite *getSprite() { return sprite; }
        thor::Animator<sf::Sprite, std::string> *getAnimator() { return animator; }
        
        /* void setOrigin(float x, float y); */
};

#endif /* ANIMATION_H */
