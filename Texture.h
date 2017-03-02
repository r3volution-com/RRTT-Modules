#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Texture {
    private:
        sf::Texture *tex;
    public:
        Texture(const char* path);
        virtual ~Texture();
        
        sf::Texture *getTexture() { return tex; }
};

#endif /* TEXTURE_H */