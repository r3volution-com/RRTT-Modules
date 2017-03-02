#include "Texture.h"

Texture::Texture(const char *path) {
    tex = new sf::Texture;
    if (!tex->loadFromFile(path)) {
        std::cerr << "Error cargando la imagen " << path;
        exit(0);
    }
}

Texture::~Texture() {
}