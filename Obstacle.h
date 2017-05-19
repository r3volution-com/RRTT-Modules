#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "libs/Hitbox.h"
#include "libs/Animation.h"

class Obstacle {
    private:
        Hitbox *hitbox;
        Animation *anim;
        Coordinate *initial;
        
        bool active;
    public:
        /**
         * 
         * @param position
         * @param s
         * @param t
         * @param newRect
         */
        Obstacle(Coordinate position, Coordinate s, Texture *t, Rect<float> newRect);
        virtual ~Obstacle();
        
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
         * 
         * @param a
         */
        void setActive(bool a) { active = a; }
        
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        bool getActive() { return active; }
};

#endif /* OBSTACLE_H */