#ifndef WEAPON_H
#define WEAPON_H

#include "libs/Coordinate.h"
#include "libs/Animation.h"
#include "libs/Hitbox.h"
#include "libs/Time.h"
#include "libs/Pie.h"

class Weapon {
    private:
        Coordinate *coor;
        Hitbox *hitbox; //ToDo: cambiar hitbox por otra cosa?
        Time *attackLength;
        Pie* pie;
        
        float degreesPerTick;
        float lengthCount;
        bool attacking;
    public:
        /**
         * 
         * @param position
         * @param size
         * @param speed
         */
        Weapon(Coordinate position, Coordinate size, float speed);
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
        
        /**
         * Lanza un ataque corto
         */
        void shortAttack(char direction);
        
        /**
         * 
         * @return 
         */
        
        bool isAttacking() { return attacking; }
        Time *getTime() { return attackLength; }
        Pie *getPie() { return pie; }
        Hitbox *getHitbox() { return hitbox; }
};

#endif /* WEAPON_H */