#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite {
    private:
        sf::Texture *tex;
        sf::Sprite *sprite;
        int clipX, clipY;
        int maxW, maxH;
    public:
        Sprite(sf::Texture *texture, int w, int h);
        virtual ~Sprite();
        
        void move(float x, float y);
        void setSize(int w, int h);
        void restoreSize();
        
        sf::Sprite *getSprite() { return sprite; }
};

#endif /* SPRITE_H */