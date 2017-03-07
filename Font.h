#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics.hpp>

class Font {
    private:
        sf::Font *font;
    public:
        Font(sf::Font *f);
        virtual ~Font();
        
        sf::Font getFont() { return *font; }
};

#endif /* FONT_H */