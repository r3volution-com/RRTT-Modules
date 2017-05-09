#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

template <class T>
class Rect {
    private:
    public:
        T x, y, w, h;
        /**
         * Crea un objeto zona de impresion
         * @param rX: Coordenada x
         * @param rY: Coordenada y
         * @param rW: Ancho
         * @param rH: Alto
         */
        Rect(T rX, T rY, T rW, T rH);
        
        /**
         * Crea un objeto zona de impresion
         * @param rect: Zona a imprimir
         */
        Rect(sf::Rect<T> rect);
        
        /**
         * Crea un objeto zona de impresion
         * @param rect: Zona a imprimir
         */
        Rect(const Rect<T>& rect);
        
        virtual ~Rect();
        
        /**
         * Establece la zona de corte
         * @param rX: Coordenada x
         * @param rY: Coordenada y
         * @param rW: Ancho
         * @param rH: Alto
         */
        void setRect(T rX, T rY, T rW, T rH);
        
        /**
         * Establece la zona de corte
         * @param rect: Zona de core
         */
        void setRect(sf::Rect<T> rect);
        
        sf::Rect<T> getRect(){
            return sf::Rect<T>(x, y, w, h);
        }
        sf::IntRect getIntRect(){
            return sf::IntRect(x, y, w, h);
        }
        sf::FloatRect getFloatRect(){
            return sf::FloatRect(x, y, w, h);
        }
        
        friend std::ostream& operator << (std::ostream &o,const Rect<float> &p);
};

inline std::ostream& operator << (std::ostream &o,const Rect<float> &p) {
    o << "(" << p.x << ", " << p.y << ", " << p.w << ", " << p.h << ")\n";
    return o;
}

#endif /* RECT_H */
