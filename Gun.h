#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>

#include "libs/Animation.h"
#include "libs/Hitbox.h"
#include "Bullet.h"

class Gun {
    private:
        Animation *gunAnimation;
        Hitbox *hitbox;
        Bullet *attack;
        
        bool active;
        
        int damage;
        
        float attackCooldown;
        float attackMaxCooldown;
    public:
        /**
         * Crea objeto arma
         * @param position: Posicion del arma 
         * @param animRect: Zona de animacion del arma
         * @param tex: Textura del arma
         */
        Gun(Coordinate position, Rect<float> *animRect, Texture *tex);
        virtual ~Gun();
        
        /**
         * Metodo para realizar ataque
         */
        void doAttack();
        
        /**
         * Actualiza la posicion del arma
         * @param coord: Coordenadas de la posicion
         */
        void setPosition(Coordinate coord);
        
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
         * Actualiza el enfriamiento del arma
         * @param atkCooldown: Enfriamiento del ataque (tipo float)
         */
        void setAttackCooldown(float atkCooldown) { attackCooldown = atkCooldown; }
        
        /**
         * Actualiza el enfriamiento maximo del ataque
         * @param atkMCooldown: Enfriamiento maximo del ataque (tipo float)
         */
        void setAttackMaxCooldown(float atkMCooldown) { attackMaxCooldown = atkMCooldown; }
        /**
         * Actualiza el dano del arma
         * @param dmg: Dano del arma
         */
        void setDamage(int dmg) { damage = dmg; }
        
        bool getActive() { return active; }
        int getDamage() { return damage; }
        float getAttackCooldown() { return attackCooldown; }
        float getAttackMaxCooldown() { return attackMaxCooldown; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return gunAnimation; }
};

#endif /* Gun_H */

