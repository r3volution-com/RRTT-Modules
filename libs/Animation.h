#ifndef ANIMATION_H
#define ANIMATION_H

#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>
#include "Coordinate.h"
#include "Rect.h"
#include "Texture.h"

class Animation {
    private:
        Texture *tex;
        Rect<float> *spriteRect;
        
        sf::Sprite *sprite;
        sf::Clock *clock;
        
        thor::AnimationMap<sf::Sprite, std::string> *animations;
        thor::Animator<sf::Sprite, std::string> *animator;
    public:
        Animation(Texture *t, Rect<float> *tRect);
        virtual ~Animation();
        
        void addAnimation(std::string name, Coordinate clipCoord, int nSprites, float duration);
        void changeAnimation(std::string name, bool loop);
        void queueAnimation(std::string name, bool loop);
        
        void initAnimator();
        void updateAnimator();
        
        void setPosition(float x, float y);
        void setPosition(Coordinate newCoord);
        void setRotation(float r);
        
        sf::Sprite *getSprite() { return sprite; }
        thor::Animator<sf::Sprite, std::string> *getAnimator() { return animator; }
        
        /* void setOrigin(float x, float y); */
};

#endif /* ANIMATION_H */
