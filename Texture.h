#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Texture {
    private:
        sf::Texture *tex;
    public:
        Texture(const char* path);
        Texture(sf::RenderTexture *t);
        virtual ~Texture();
        
        sf::RenderTexture *getRenderTexture(int w, int h);
        
        sf::Texture *getTexture() { return tex; }
};

#endif /* TEXTURE_H */