#ifndef ENTITY_H
#define ENTITY_H

#include "InterpolatedCoordinate.h"
#include "Hitbox.h"
#include "Texture.h"
#include "Animation.h"

class Entity {
    private:
        int width, height;
        InterpolatedCoordinate *coor;
        
        float speed;
        
        Hitbox *hitbox;
        
        Animation *anim;
    public:
        Entity(Rect* newRect, float sp);
        virtual ~Entity();
        
        void loadAnimation(Texture *t, Coordinate *clipCoord, int nS, float d);
        void move(float dirX, float dirY);
        bool collision(Hitbox *other);
        
        void setSize(int w, int h) { width = w; height = h; }
        void setSpeed(float sp) { speed = sp; }
        void setPosition(float x, float y){ coor->setCoordinate(x, y); }
        
        int getWidth() { return width; }
        int getHeight() { return height; }
        Coordinate getCoordinate() { return coor->getIC(); }
        float getSpeed() { return speed; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return anim; }
};

#endif /* Entity_H */

