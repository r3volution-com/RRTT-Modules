#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include "Font.h"

class Text {
    private:
        Font *font;
        sf::Text *text;
    public:
        Text(std::string t, float x, float y, Font *f);
        virtual ~Text();
        
        void setStyles(sf::Color color, sf::Color outlineColor, int outlineThickness, int size); 
        void setText(std::string t);
        void setPosition(float x, float y) { text->setPosition(x, y); }
        sf::Text *getText();
};

#endif /* TEXT_H */