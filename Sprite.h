#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Coordinate.h"

class Sprite {
    private:
        Texture *tex;
        sf::Sprite *sprite;
        sf::IntRect *spriteRect;
        int clipX, clipY;
        int maxW, maxH;
        float actW, actH;
    public:
        Sprite(Texture *texture, int w, int h, int cX, int cY);
        virtual ~Sprite();
        
        void move(float x, float y);
        void setPosition(float x, float y);
        void setSize(float w, float h);
        void changeSpriteRect(int cX, int cY, int w, int h);
        void restoreSize();
        float getW(){return actW;}
        float getH(){return actH;}
        int getMaxW(){return maxW;}
        int getMaxH(){return maxH;}
        Coordinate getPosition();
        sf::Sprite getSprite() { return *sprite; }
        sf::IntRect getSpriteRect() { return *spriteRect; }
};

#endif /* SPRITE_H */