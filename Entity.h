#ifndef ENTITY_H
#define ENTITY_H

#include "libs/InterpolatedCoordinate.h"
#include "libs/Hitbox.h"
#include "libs/Animation.h"

class Entity {
    private:
        InterpolatedCoordinate *coor;
        Coordinate *size;
        Hitbox *hitbox;
        Animation *anim;
        Coordinate *initial;
        float speed;
    public:
        /**
         * Creacion del objeto entidad
         * @param position: Posicion de la entidad
         * @param size: Tamano de la entidad
         * @param sp: Velocidad del personaje al moverse por el mapa
         */
        Entity(Coordinate position, Coordinate size, float sp);
        virtual ~Entity();
        
        /**
         * Añade sprite a la entidad
         * @param t: Textura de la entidad
         * @param newRect: Nueva zona en la que dibujar el sprite entidad
         */
        void setSprite(Texture *t, Rect<float> newRect);
        
        /**
         * Movimiento de la entidad
         * @param dirX: Movimiento en la coordenada X
         * @param dirY: Movimiento en la coordenada Y
         * @param speed: velocidad
         */
        void move(float dirX, float dirY, float sp);
        
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
        void setPosition(Coordinate newCoor);
        /**
         * Actualiza la posicion de la entidad
         * @param x: Coordenada X de la posicion
         * @param y: Coordenada Y de la posicion
         */
        void setPosition(float x, float y);
        /**
         * Actualiza la posicion de la entidad
         * @param newCoor: Nueva coordenada de posicion
         */
        void updatePosition(Coordinate newCoor);
        /**
         * Actualiza la posicion de la entidad
         * @param x: Coordenada X de la posicion
         * @param y: Coordenada Y de la posicion
         */
        void updatePosition(float x, float y);
        
        InterpolatedCoordinate *getState() { return coor; }
        Coordinate *getCoordinate() { return coor->getCoordinate(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getSpeed() { return speed; }
        Coordinate *getSize(){ return size; }
        Coordinate *getInitialCoordinate() { return initial;}
};

#endif /* Entity_H */
