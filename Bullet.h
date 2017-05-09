#ifndef BULLET_H
#define BULLET_H

#include "libs/InterpolatedCoordinate.h"
#include "libs/Hitbox.h"
#include "libs/Animation.h"
class Bullet {
    private:
        InterpolatedCoordinate *coor;
        Hitbox *hitbox;
        Animation *anim;
        Coordinate *initial;
        
        float duration;
    public:
        /**
         * Creacion del objeto bala
         * @param position: Posicion de la bala. Tipo Coordinates
         * @param size: Tamano de la bala
         * @param d: duracion de la bala
         */
        Bullet(Coordinate position, Coordinate size, float d); //ToDo: bullet
        virtual ~Bullet();
        
        /**
         * Crea la animacion para la bala
         * @param t: textura de la bala
         * @param newRect: posicion de la bala en el spritesheet
         */
        void setAnimation(Texture *t, Rect<float> newRect);
        
        /**
         * Actualiza la posicion de la bala. Tipo Coordinate
         * @param newCoor: Coordenada
         */
        void setPosition(Coordinate newCoor);
        
        /**
         * Actualiza la posicion de la bala.
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setPosition(float x, float y);
        //void move(float dirX, float dirY);
        
        /**
         * Comprueba que una hitbox colisione con otra
         * @param other: Hitbox con la que se colisiona
         * @return: Booleano
         */
        bool collision(Hitbox *other);
        
        InterpolatedCoordinate *getState() { return coor; }
        Coordinate *getCoordinate() { return coor->getCoordinate(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        Coordinate *getInitialCoordinate() { return initial; }
        float getDuration() { return duration; }
};

#endif /* BULLET_H */