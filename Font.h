#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Font {
    private:
        sf::Font *font;
    public:
        Font(std::string path);
        virtual ~Font();
        
        sf::Font getFont() { return *font; }
};

#endif /* FONT_H */