#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Font {
    private:
        static sf::Font *font;
    public:
        Font(const char *path);
        virtual ~Font();
        
        sf::Font getFont() { return *font; }
};

#endif /* FONT_H */