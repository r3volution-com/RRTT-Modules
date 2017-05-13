#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Rect.h"
#include "Coordinate.h"

class Hitbox {
    private:
    public:
        sf::Rect<float> *hitbox;
        
        /**
         * Crea el objeto hitbox
         * @param x: Coordenada x
         * @param y: Coordenada y
         * @param w: Ancho
         * @param h: Alto
         */
        Hitbox(float x, float y, int w, int h);
        
        /**
         * Zona en la que se imprime la hitbox
         * @param h: hitbox
         */
        Hitbox(Rect<float> h);
        virtual ~Hitbox();
        
        /**
         * Establece la posicion
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setPosition(float x, float y);
        
        /**
         * Establece la posicion
         * @param newCoor: Coordenada
         */
        void setPosition(Coordinate newCoor);
        
        /**
         * Comprueba si dos objetos colisionan
         * @param other
         * @return 
         */
        bool checkCollision(Hitbox *other);
        
        /**
         * 
         * @param other
         * @param speed
         * @return 
         */
        Coordinate resolveCollision(Hitbox *other, Coordinate speed);
        
        friend std::ostream& operator << (std::ostream &o,const Hitbox &p);
};

inline std::ostream& operator << (std::ostream &o,const Hitbox &p) {
    o << "(" << p.hitbox->left << ", " << p.hitbox->top << ", " << p.hitbox->width << ", " << p.hitbox->height << ")";
    return o;
}

#endif /* HITBOX_H *///Game::Instance()->getLevelState()->getLevel()->getMap()