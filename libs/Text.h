#ifndef TEXT_H
#define TEXT_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include "Font.h"
#include "Coordinate.h"

class Text {
    private:
        Font *font;
        sf::Text *text;
        bool centerOrigin;
    public:
        /**
         * Creacion del objeto texto
         * @param t: Texto a escribir
         * @param position: Posicion del texto a escribir
         * @param f: Fuente del texto a escribir
         * @param centerOrigin: Centro de origen del texto a escribiir
         */
        Text(std::string t, Coordinate position, Font *f, bool centerOrigin);
        virtual ~Text();
        
        /**
         * Establece el estilo del textoo¡
         * @param color: Color del texo
         * @param size
         */
        void setTextStyle(sf::Color color, int size);
        
        /**
         * Establece el estilo del textoo¡
         * @param color: Color del texo
         * @param size
         */
        void setOutlineStyle(sf::Color outlineColor, int outlineThickness);
        
        /**
         * Establece el texto.
         * @param t: Texto a establecer
         */
        void setText(std::string t);
        /**
         * Establece la posicion 
         * @param position: posicion
         */
        void setPosition(Coordinate position) { text->setPosition(position.x, position.y); }
        sf::Text *getText();
};

#endif /* TEXT_H */