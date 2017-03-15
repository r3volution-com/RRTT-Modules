#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>
#include <cstddef>
#include <SFML/Graphics/Rect.hpp>

class Hitbox {
    private:
    public:
        sf::Rect<float> *hitbox;
        
        Hitbox(float x, float y, int w, int h);
        virtual ~Hitbox();
        
        void move(float x, float y);
        bool checkCollision(Hitbox *other);
};

#endif /* HITBOX_H */