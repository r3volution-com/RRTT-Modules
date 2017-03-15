#include "Font.h"

Font::Font(const char *path) {
    font = new sf::Font();
    if (!font->loadFromFile(path)){
        std::cerr << "Error cargando la fuente " << path;
        exit(0);
    }
}

Font::~Font() {
}