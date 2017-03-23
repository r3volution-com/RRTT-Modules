#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Coordinate.h"
#include "Texture.h"
#include "InterpolatedCoordinate.h"
#include "Rect.h"

class Animation {
    private:
        Texture *tex;
        Rect<float> *rectSprite;
        InterpolatedCoordinate *coordinate;
        Coordinate *clipCoordinate;
        sf::Sprite *sprites;
        sf::Clock *clock;
        float delay;
        int currentSprite;
        int numSprites;
        
        void changeCurrentSprite();
    public:
        Animation(Texture *t, Rect<float> *tRect, int nS, float d);
        virtual ~Animation();
        
        void setPosition(float x, float y);
        void setPosition(Coordinate *newCoord);
        
        void move(float x, float y);
        void changeSpriteRect(Rect<float> *newRect);
        
        sf::Sprite getCurrentSprite();
};

#endif /* ANIMATION_H */