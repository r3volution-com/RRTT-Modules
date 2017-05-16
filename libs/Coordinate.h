#ifndef COORDINATE_H
#define COORDINATE_H

#include <SFML/System.hpp>
#include <ostream>

class Coordinate {
    private:

    public:
        float x, y;
        /**
         * Crea el objeto coordenada a partir de su posicion
         * @param xC: coordenada x
         * @param yC: coordenada y
         */
        Coordinate(float xC, float yC);
        /**
         * Crea el objeto coordenada a partir de un vector int
         * @param coor: coordenadas
         */
        Coordinate(sf::Vector2i coor);
        /**
         * Crea el objeto coordenada a partir de un vector float
         * @param coor: coordenadas
         */
        Coordinate(sf::Vector2f coor);
        
        /**
         * Copia una coordenada
         * @param coor
         */
        Coordinate(const Coordinate& coor);
        virtual ~Coordinate();
        
        /**
         * Establece las coordenadas
         * @param xC: Coordenada x
         * @param yC: Coordenada y
         */
        void setCoordinate(float xC, float yC);
        
        /**
         * Establece las coordenadas
         * @param coor: Tipo Coordinate, coordenadas
         */
        void setCoordinate(Coordinate coor);
        
        sf::Vector2f getV2fCoordinate(){
            return sf::Vector2f(x, y);
        }
        
        bool operator ==(const Coordinate &p) const;
        bool operator !=(const Coordinate &p) const;
        Coordinate operator +(const Coordinate &p) const;
        Coordinate operator +(const float &num) const;
        
        friend std::ostream& operator << (std::ostream &o,const Coordinate &p);
};

inline std::ostream& operator << (std::ostream &o,const Coordinate &p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

#endif /* COORDINATE_H */
