#include "Texture.h"

Texture::Texture(const char *path) {
    tex = new sf::Texture;
    if (!tex->loadFromFile(path)) {
        std::cerr << "Error cargando la imagen " << path;
        exit(0);
    }
    render = false;
    rTex = 0;
}

Texture::Texture(sf::RenderTexture *t){
    tex = 0;
    rTex=t;
    render = true;
}

Texture::~Texture() {
    delete tex;
    delete rTex;
    tex = NULL;
    rTex = NULL;
}

sf::RenderTexture *Texture::createRenderTexture(int w, int h) { 
    sf::RenderTexture *te = new sf::RenderTexture();
    te->create(w, h);
    te->clear();
    return te;
}
sf::Texture *Texture::getTexture(){
    if (render) {
        sf::Texture *t = new sf::Texture(rTex->getTexture());
        return t;
    } else return tex;
}