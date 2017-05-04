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
        float speed;
    public:
        /**
         * Creacion del objeto bala
         * @param position: Posicion de la bala. Tipo Coordinates
         * @param t: Textura de la bala
         * @param newRect: Zona en la que se imprime la bala
         * @param sp: Velocidad de animacion de la bala
         */
        Bullet(Coordinate position, Texture *t, Rect<float> newRect, float sp); //ToDo: bullet
        
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
        virtual ~Bullet();
        InterpolatedCoordinate *getState() { return coor; }
        Coordinate *getCoordinate() { return coor->getCoordinate(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getSpeed() { return speed; }
        Coordinate *getInitialCoordinate() { return initial;}
};

#endif /* BULLET_H */