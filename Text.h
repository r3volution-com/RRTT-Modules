#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include "Font.h"
#include "Coordinate.h"

class Text {
    private:
        Font *font;
        sf::Text *text;
        bool centerOrigin;
    public:
        Text(std::string t, Coordinate position, Font *f, bool centerOrigin);
        virtual ~Text();
        
        void setStyles(sf::Color color, sf::Color outlineColor, int outlineThickness, int size); 
        void setText(std::string t);
        void setPosition(Coordinate position) { text->setPosition(position.x, position.y); }
        sf::Text *getText();
};

#endif /* TEXT_H */