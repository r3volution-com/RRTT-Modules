#ifndef BULLET_H
#define BULLET_H

#include "libs/InterpolatedCoordinate.h"
#include "libs/Hitbox.h"
#include "libs/Animation.h"
class Bullet {
    private:
        Hitbox *hitbox;
        Animation *anim;
        int damage;
        
        int type;
        
        float duration;
    public:
        /**
         * Creacion del objeto bala
         * @param position: Posicion de la bala. Tipo Coordinates
         * @param d: duracion de la bala
         * @param t: tipo de la bala
         */
        Bullet(Coordinate size, float d, int t);
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
        
        /**
         * Actualiza el dano del arma
         * @param dmg: Dano del arma
         */
        void setDamage(int dmg) { damage = dmg; }
        
        int getDamage() { return damage; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getDuration() { return duration; }
        int getType(){return type;}
};

#endif /* BULLET_H */