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
        
        Time *gunCooldown;
        float maxCooldown;
        bool active;
        
        Bullet *attack;
        Time *bulletLifetime; //ToDo: No estoy seguro si Gun deberia manejar esto
        bool bulletLoaded;
        
        char type;
    public:
        /**
         * Crea objeto arma
         * @param cd: cooldown
         */
        Gun(float cd);
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
        void setCooldown(float aux);
        /**
         * Define el cooldown del arma
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
        
        bool getActive() { return active; }
        Time *getBulletLifetime() { return bulletLifetime; }
        Time *getGunCooldown() { return gunCooldown; }
        Animation *getAnimation(){ return gunAnimation; }
        Bullet *getBullet(){return attack;}
        Coordinate *getCoordinate(){return coor;}
};

#endif /* Gun_H */

