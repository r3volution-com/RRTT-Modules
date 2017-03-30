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
         * Creación de una animación
         * @param t: Puntero a textura
         * @param *tRect: Puntero a zona a mostrar de la textura
         */
        Animation(Texture *t, Rect<float> *tRect);
        virtual ~Animation();
        
        /**
         * Añadir animacion
         * @param name: Nombre de la animacion
         * @param clipCoord: Coordenada de la textura del primer sprite de la animacion
         * @param nSprites: Numero de sprites que ejecuta
         * @param duration: Duracion de los sprites
         */
        void addAnimation(std::string name, Coordinate clipCoord, int nSprites, float duration);
        
        /**
         * Cambiar una animacion por otra
         * @param name: Nombre de la animacion
         * @param loop: Una animacion se hace una vez si es false y muchas si es true
         */
        void changeAnimation(std::string name, bool loop);
        
        /**
         * Poner una animacion en cola para cuando acabe la actual
         * @param name: Nombre de la animacion
         * @param loop: Una animacion se hace una vez si es false y muchas si es true
         */
        void queueAnimation(std::string name, bool loop);
        
        /**
         * Inicia la animacion
         */
        void initAnimator();
        
        /**
         * Actualiza la animacion
         */
        void updateAnimator();
        
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
        void setPosition(Coordinate newCoord);
        
        /**
         * Actualiza la rotacion de la animacion
         * @param r: Grados a rotar
         */
        void setRotation(float r);

        sf::Sprite *getSprite() { return sprite; }
        thor::Animator<sf::Sprite, std::string> *getAnimator() { return animator; }
        
        /*void move(float x, float y);
        void setOrigin(float x, float y);*/
};

#endif /* ANIMATION_H */
