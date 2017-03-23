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
        Rect *actualSpriteRect;
        Rect *originalSpriteRect;
    public:
        Sprite(Texture *texture, Rect *spriteRect);
        virtual ~Sprite();
        
        void move(float x, float y);
        void setPosition(Coordinate *pos);
        void setRotation(float r);
        void setSize(float w, float h);
        void changeSpriteRect(Rect *spriteRect);
        void restoreSize();
        
        Coordinate getPosition();
        sf::Sprite getSprite() { return *sprite; }
        Rect *getActualSpriteRect() { return actualSpriteRect; }
        Rect *getOriginalSpriteRect() { return originalSpriteRect; }
};

#endif /* SPRITE_H */