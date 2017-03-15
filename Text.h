#ifndef TEXT_H
#define TEXT_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include "Font.h"

class Text {
    private:
        Font *font;
        sf::Text *text;
    public:
        Text(std::string t, float x, float y, sf::Color color, Font *f); //ToDo: color, estilo, etc...
        virtual ~Text();
        
        void setText(std::string t) { text->setString(t); }
        void setPosition(float x, float y) { text->setPosition(x, y); }
        sf::Text getText() { return *text; }
};

#endif /* TEXT_H */