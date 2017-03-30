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
         * @param position:
         * @param t
         * @param newRect
         * @param sp
         */

        Entity(Coordinate position, Texture *t, Rect<float> newRect, float sp);
        virtual ~Entity();
        
        void move(float dirX, float dirY);
        bool collision(Hitbox *other);
        
        void setSpeed(float sp) { speed = sp; }
        void setPosition(Coordinate newCoor){ coor->setCoordinate(newCoor); anim->setPosition(newCoor); hitbox->setPosition(newCoor);}
        void setPosition(float x, float y){ coor->setCoordinate(x, y); anim->setPosition(x, y); hitbox->setPosition(x, y);}
        
        Coordinate *getCoordinate() { return coor->getIC(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getSpeed() { return speed; }
};

#endif /* Entity_H */
