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
        Animation *anim;
        Hitbox *hitbox;
        Time *attackLength;
        Pie* pie;
        
        float degreesPerTick;
        float lengthCount;
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
         * Crea la animacion
         * @param animRect: Zona de animacion del arma
         * @param tex: Textura del arma
         */
        void setAnimation(Texture *tex, Rect<float> animRect);
        
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
        void loadAttack(); //ToDo: permitir angulo inicial
        
        /**
         * Lanza el ataque
         */
        void doAttack();
        
        /**
         * 
         * @return 
         */
        Pie *getPie() { return pie; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
};

#endif /* WEAPON_H */