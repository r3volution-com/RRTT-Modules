#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Coordinate.h"
#include "Rect.h"

class Sprite {
    private:
        Texture *tex;
        sf::Sprite *sprite;
        Rect<float> *actualSpriteRect;
        Rect<float> *originalSpriteRect;
    public:
        Sprite(Texture *texture, Rect<float> *spriteRect);
        virtual ~Sprite();
        
        void move(float x, float y);
        void setPosition(Coordinate *pos);
        void setSize(float w, float h);
        void changeSpriteRect(Rect<float> *spriteRect);
        void restoreSize();
        
        Coordinate getPosition();
        sf::Sprite getSprite() { return *sprite; }
        Rect<float> *getActualSpriteRect() { return actualSpriteRect; }
        Rect<float> *getOriginalSpriteRect() { return originalSpriteRect; }
};

#endif /* SPRITE_H */