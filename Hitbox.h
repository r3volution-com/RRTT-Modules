#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include "Rect.h"
#include "Coordinate.h"

class Hitbox {
    private:
    public:
        sf::Rect<float> *hitbox;
        
        Hitbox(float x, float y, int w, int h);
        Hitbox(Rect *h);
        virtual ~Hitbox();
        
        void setPosition(float x, float y);
        void setPosition(Coordinate *newCoor);
        void move(float x, float y);
        bool checkCollision(Hitbox *other);
};

#endif /* HITBOX_H */