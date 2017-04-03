#ifndef ENTITY_H
#define ENTITY_H

#include "libs/InterpolatedCoordinate.h"
#include "libs/Hitbox.h"
#include "libs/Animation.h"

class Entity {
    private:
        InterpolatedCoordinate *coor;
        Hitbox *hitbox;
        Animation *anim;
        
        float speed;
    public:
        /**
         * Creacion del objeto entidad
         * @param position: Posicion de la entidad
         * @param t: Textura de la entidad
         * @param newRect: Nueva zona en la que dibujar el sprite entidad
         * @param sp: Velocidad del personaje al moverse por el mapa
         */
        Entity(Coordinate position, Texture *t, Rect<float> newRect, float sp);
        virtual ~Entity();
        
        /**
         * Movimiento de la entidad
         * @param dirX: Movimiento en la coordenada X
         * @param dirY: Movimiento en la coordenada Y
         */
        void move(float dirX, float dirY);
        /**
         * Colision de la entidad
         * @param other: Hitbox del elemento que choca con la entidad
         * @return 
         */
        bool collision(Hitbox *other);
        /**
         * Actualiza la velocidad de la entidad
         * @param sp: Velocidad de la entidad
         */
        void setSpeed(float sp) { speed = sp; }
        /**
         * Actualiza la posicion de la entidad
         * @param newCoor: Nueva coordenada de posicion
         */
        void setPosition(Coordinate newCoor){ coor->setCoordinate(newCoor); anim->setPosition(newCoor); hitbox->setPosition(newCoor);}
        /**
         * Actualiza la posicion de la entidad
         * @param x: Coordenada X de la posicion
         * @param y: Coordenada Y de la posicion
         */
        void setPosition(float x, float y){ coor->setCoordinate(x, y); anim->setPosition(x, y); hitbox->setPosition(x, y);}
        
        Coordinate getCoordinate() { return coor->getIC(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getSpeed() { return speed; }
};

#endif /* Entity_H */
