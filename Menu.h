#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "libs/Font.h"
#include "libs/Hitbox.h"
#include "libs/Sprite.h"
#include "Button.h"

class Menu {
    private:
        Sprite *background;
        Texture *buttonLayout;
        Rect<float> *buttonTextureRect;
        std::vector<Button*> buttons; 
        Font *buttonFont;
    public:
        /**
         * Crea el objeto menu
         * @param bg: Textura del fondo del menu
         * @param bLayout: Textura del menu
         * @param tRect: Tamano de los botones
         * @param bFont: Fuente del menu
         * @param numButtons: Numero de botones del menu
         */
        Menu(Texture *bg, Texture *bLayout, Rect<float> *tRect, Font* bFont);
        virtual ~Menu();
        
        /**
         * Anadir boton
         * @param position: Posicion del boton (tipo coord)
         * @param text: Texto del boton a anadir
         * @param color: Color del boton
         * @param outlineColor: Color del borde del boton
         * @param size: Tamano del boton
         * @return 
         */
        void addButton(Coordinate position, std::string text, sf::Color color, sf::Color outlineColor, int size);
        
        /**
         * Comprueba si esta pasando el raton por encima de un boton
         * @param mouse: Posicion del raton (tipo hitbox)
         */
        void checkHover(Hitbox* mouse);
        
        /**
         * Comprueba los clicks realizados
         * @return 
         */
        int checkClicks();
        
        /**
         * Dibuja el menu
         * @param window: Ventana en la que dibujar
         */
        void drawMenu();
};

#endif /* MENU_H */
