#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Texture.h"

class Sprite {
    private:
        Texture *tex;
        sf::Sprite *sprite;
        sf::IntRect *spriteRect;
        int clipX, clipY;
        int maxW, maxH;
    public:
        Sprite(Texture *texture, int w, int h, int cX, int cY);
        virtual ~Sprite();
        
        void move(float x, float y);
        void setPosition(float x, float y);
        void setSize(int w, int h);
        void changeSpriteRect(int cX, int cY, int w, int h);
        void restoreSize();
        int getW(){return maxW;}
        int getH(){return maxH;}
        sf::Sprite getSprite() { return *sprite; }
        sf::IntRect getSpriteRect() { return *spriteRect; }
};

#endif /* SPRITE_H */