#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
    private:
        sf::Texture *tex;
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
        Animation(sf::Texture *t, int w, int h, int cX, int cY, int nS, float d);
        virtual ~Animation();
        
        void move(float x, float y);
        
        sf::Sprite getCurrentSprite();
};

#endif /* ANIMATION_H */