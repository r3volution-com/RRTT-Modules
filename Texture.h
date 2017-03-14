#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Texture {
    private:
        sf::Texture *tex;
        sf::RenderTexture *rTex;
    public:
        Texture(const char* path);
        Texture(sf::RenderTexture *t);
        virtual ~Texture();
        
        sf::RenderTexture *getRenderTexture(int w, int h);
        
        sf::Texture *getTexture() { return tex; }
        sf::RenderTexture *getRenderTexture() { return rTex; }
};

#endif /* TEXTURE_H */