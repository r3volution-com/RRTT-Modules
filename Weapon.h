#ifndef WEAPON_H
#define WEAPON_H

#include <Thor/Vectors.hpp>
#include "libs/Coordinate.h"
#include "libs/Animation.h"
#include "libs/Hitbox.h"
#include "libs/Time.h"
#include "libs/Pie.h"

class Weapon {
    private:
        Coordinate *coor;
        Hitbox *hitbox;
        Time *attackLength;
        Pie* pie;
        thor::PolarVector2<float> *vector;
        
        float degreesPerTick;
        float lengthCount;
        float animSpeed;
        float pieRadius;
        float pieResolution;
        
        int dmg;
        
        bool loadingAttack;
        bool isLong;
        
        char dir;
    public:
        /**
         * 
         * @param position
         * @param size
         * @param speed
         */
        Weapon(Coordinate position, Coordinate size, float speed, float animationSpeed);
        virtual ~Weapon();
        
        /**
         * Actualiza la posicion del arma
         * @param coord: Coordenadas de la posicion
         */
        void setPosition(float x, float y);
        
        /**
         * Actualiza la posicion del arma
         * @param coord: Coordenadas de la posicion
         */
        void setPosition(Coordinate coord);
        
        /**
         * Carga el ataque
         * @param angle: angulo
         */
        void loadAttack(char direction);
        
        /**
         * Lanza el ataque
         */
        int releaseAttack();
        
        void update();
        
        /**
         * Mueve la hitbox
         */
        bool detectCollisions(Hitbox *other);
        
        /**
         * Lanza un ataque corto
         */
        void shortAttack(char direction);
        
        /**
         * Actualiza el dano realizado
         * @param damage: dano realizado
         */
        void setDamage(int damage) { dmg = damage; }
        
        int getDamage() { return dmg; }
        bool isAttacking() { return loadingAttack; }
        char getDirection() { return dir; }
        Time *getTime() { return attackLength; }
        Pie *getPie() { return pie; }
        Hitbox *getHitbox() { return hitbox; }
};

#endif /* WEAPON_H */