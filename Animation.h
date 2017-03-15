#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Texture.h"

class Animation {
    private:
        Texture *tex;
        sf::Sprite *sprites;
        sf::IntRect *rectSprite;
        sf::Clock *clock;
        float delay;
        int currentSprite;
        int numSprites;
        int width, height;
        int clipX, clipY;
        
        void changeCurrentSprite();
    public:
        Animation(Texture *t, int w, int h, int cX, int cY, int nS, float d);
        virtual ~Animation();
        
        void move(float x, float y);
        void changeSpriteRect(int cX, int cY, int w, int h);
        
        sf::Sprite getCurrentSprite();
};

#endif /* ANIMATION_H */