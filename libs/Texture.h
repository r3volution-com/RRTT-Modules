#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Texture {
    private:
        sf::Texture *tex;
        sf::RenderTexture *rTex;
        
        bool render;
    public:
        Texture(const char* path);
        Texture(sf::RenderTexture *t);
        virtual ~Texture();
        
        sf::RenderTexture *createRenderTexture(int w, int h);
        
        sf::Texture *getTexture();
        sf::RenderTexture *getRenderTexture() { return rTex; }
};

#endif /* TEXTURE_H */