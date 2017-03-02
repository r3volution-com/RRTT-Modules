#ifndef ENTITY_H
#define ENTITY_H

#include "Hitbox.h"
#include "Texture.h"
#include "Animation.h"

class Entity {
    private:
        int width;
        int height;
        float posX;
        float posY;
        
        float speed;
        
        Hitbox *hitbox;
        
        Animation *anim;
    public:
        Entity();
        virtual ~Entity();
        
        void loadAnimation(Texture *t, int w, int h, int cX, int cY, int nS, float d);
        void move(float dirX, float dirY);
        bool collision(Hitbox *other);
        
        void setSize(int w, int h) { width = w; height = h; }
        void setPosition(float x, float y) { posX = x; posY = y; }
        void setSpeed(float sp) { speed = sp; }
        
        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return posX; }
        float getY() { return posY; }
        float getSpeed() { return speed; }
        Hitbox getHitbox() { return *hitbox; }
        Animation *getAnimation(){ return anim; }
};

#endif /* Entity_H */

