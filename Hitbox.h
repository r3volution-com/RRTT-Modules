#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Rect.h"
#include "Coordinate.h"

class Hitbox {
    private:
    public:
        sf::Rect<float> *hitbox;
        
        Hitbox(float x, float y, int w, int h);
        Hitbox(Rect<float> h);
        virtual ~Hitbox();
        
        void setPosition(float x, float y);
        void setPosition(Coordinate newCoor);
        
        bool checkCollision(Hitbox *other);
};

#endif /* HITBOX_H */