#include "Font.h"

Font::Font(std::string path) {
    font = new sf::Font();
    if (!font->loadFromFile(path)){
        std::cerr << "Error cargando la fuente " << path;
        exit(0);
    }
}

Font::~Font() {
    delete font;
    font = NULL;
}