#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
    private:
        int width;
        int height;
        float posX;
        float posY;
        
        float speed;
        
        Rect<float> hitbox;
        
        Texture texture;
        Sprite sprite;
    public:
        Entity();
        virtual ~Entity();
        
        void loadSprite(Texture texture);
        void move(float dirX, float dirY);
        bool collision(Rect<float> other);
        
        void setSize(int w, int h) { width = w; height = h; }
        void setPosition(float x, float y) { posX = x; posY = y; }
        void setSpeed(float sp) { speed = sp; }
        
        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return posX; }
        float getY() { return posY; }
        float getSpeed() { return speed; }
        Rect<float> getHitbox() { return hitbox; }
        Sprite getSprite(){ return sprite; }
};

#endif /* Entity_H */

