#ifndef BUTTON_H
#define BUTTON_H

#include "libs/Text.h"
#include "libs/Hitbox.h"
#include "libs/Sprite.h"
#include "libs/Rect.h"

class Button {
    private:
        Text *text;
        Hitbox *hitbox;
        Sprite *buttonLayout;
        Rect<float> *buttonData;
        
        sf::Color *outlineColor;
        sf::Color *outlineColorHover;
        int outlineSize;
        
        bool isHover;
    public:
        /**
         * Contruye el boton
         * @param pos: Coordenadas de la posicion del boton
         * @param bL: Puntero de textura del fondo del layout
         * @param textureRect: Zona a mostrar de la textura del boton
         */

        Button(Coordinate pos, Texture *bL, Rect<float> textureRect);
        virtual ~Button();
        
        /**
         * Actualiza el texto mostrado
         * @param t: String con el texto a mostrar
         * @param color: Color del texto
         * @param f: Puntero a la fuente del texto
         * @param size: Tamano de la fuente del texto
         */
        void setText(std::string t, sf::Color color, Font *f, int size);
        
        /**
         * 
         * @param outlineSize
         * @param outlineColor
         * @param outLineColorHover
         */
        void setOutline(int oS, sf::Color oC, sf::Color oCH);
        
        /**
         * Cuando el raton se halla sobre el boton
         * @param *mouse: Puntero de tipo hitbox que hace referencia al raton (cuando la hitbox de este se cruza con la del boton)
         */
        void hover(Hitbox *mouse);
        bool getHover() { return isHover; }
        
        /**
         * Dibuja el boton en la ventana actual
         * @param window: Puntero que hace referencia a la ventana actual
         */
        void draw();
        
        Sprite *getSprite() {return buttonLayout;}
        
};

#endif /* BUTTON_H */
