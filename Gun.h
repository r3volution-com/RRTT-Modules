#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>

#include "libs/Time.h"
#include "libs/Animation.h"
#include "libs/Hitbox.h"
#include "Bullet.h"

class Gun {
    private:
        Coordinate *coor;
        Animation *gunAnimation;
        Hitbox *hitbox;
        
        Time *gunCooldown;
        float maxCooldown;
        int damage;
        bool active;
        
        Bullet *attack;
        Time *bulletLifetime;
        bool bulletLoaded;
    public:
        /**
         * Crea objeto arma
         * @param position: Posicion del arma 
         * @param size: tamano del arma
         * @param cd: cooldown
         */
        Gun(Coordinate position, Coordinate size, float cd);
        virtual ~Gun();
        
        /**
         * Crea la animacion
         * @param animRect: Zona de animacion del arma
         * @param tex: Textura del arma
         */
        void setAnimation(Texture *tex, Rect<float> animRect);
        
        /**
         * Metodo para realizar ataque
         */
        void doAttack();
        
        /**
         * Actualiza la posicion de las balas
         */
        void update(Coordinate position, float angle);
        
        /**
         * Actualiza la posicion del arma
         * @param coord: Coordenadas de la posicion
         */
        void setPosition(Coordinate coord);
        
        /**
         * Actualiza la posicion del arma
         * @param coord: Coordenadas de la posicion
         */
        void setPosition(float x, float y);
        
        /**
         * Actualiza el ataque del arma
         * @param atk: Ataque del arma
         */
        void setAttack(Bullet *atk);

        /**
         * Define si el arma esta activa o no
         */
        void setActive();
         /**
          * setea la animacion del arama a derecha
          */
        void derecha();
          /**
          * setea la animacion del arama a isquierda
          */
        void inversa();
        /**
         * setea la animacion del arma para cuando mira arriba
         */ 
        void atras();
        
        /**
         * Actualiza el dano del arma
         * @param dmg: Dano del arma
         */
        void setDamage(int dmg) { damage = dmg; }
        
        bool getActive() { return active; }
        Time *getBulletLifetime() { return bulletLifetime; }
        Time *getGunCooldown() { return gunCooldown; }
        int getDamage() { return damage; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return gunAnimation; }
        Bullet *getBullet(){return attack;}
        Coordinate *getCoordinate(){return coor;}
};

#endif /* Gun_H */

