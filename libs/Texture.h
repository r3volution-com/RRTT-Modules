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
        /**
         * Crea el objeto textura
         * @param path: Ruta de la textura
         */
        Texture(const char* path);
        /**
         * Crea el objeto textura
         * @param t: Textura a crear
         */
        Texture(sf::RenderTexture *t);
        virtual ~Texture();
        
        /**
         * Crea un render de la textura
         * @param w: Ancho
         * @param h: Alto
         * @return 
         */
        sf::RenderTexture *createRenderTexture(int w, int h);
        
        sf::Texture *getTexture();
        sf::RenderTexture *getRenderTexture() { return rTex; }
};

#endif /* TEXTURE_H */