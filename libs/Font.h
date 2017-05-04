#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Font {
    private:
        sf::Font *font;
    public:
        /**
         * Creacion del objeto fuente
         * @param path: Ruta de la fuente
         */
        Font(std::string path);
        virtual ~Font();
        
        sf::Font *getFont() { return font; }
};

#endif /* FONT_H */