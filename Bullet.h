#ifndef BULLET_H
#define BULLET_H

#include "libs/InterpolatedCoordinate.h"
#include "libs/Hitbox.h"
#include "libs/Animation.h"
class Bullet {
    private:
        InterpolatedCoordinate *coor;
        Hitbox *hitbox;
        Animation *anim;
        Coordinate *initial;
        float speed;
    public:
        Bullet(Coordinate position, Texture *t, Rect<float> newRect, float sp); //ToDo: bullet
        void setPosition(Coordinate newCoor);
        void setPosition(float x, float y);
        bool collision(Hitbox *other);
        virtual ~Bullet();
        InterpolatedCoordinate *getState() { return coor; }
        Coordinate *getCoordinate() { return coor->getCoordinate(); }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
        float getSpeed() { return speed; }
        Coordinate *getInitialCoordinate() { return initial;}
};

#endif /* BULLET_H */