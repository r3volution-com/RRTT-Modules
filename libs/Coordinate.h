#ifndef COORDINATE_H
#define COORDINATE_H

#include <SFML/System.hpp>
#include <ostream>

class Coordinate {
    private:

    public:
        float x, y;
        /**
         * Crea el objeto coordenada
         * @param xC: coordenada x
         * @param yC: coordenada y
         */
        Coordinate(float xC, float yC);
        /**
         * Crea una vector de coordenadas
         * @param coor: coordenadas
         */
        Coordinate(sf::Vector2i coor);
        /**
         * Crea una vector de coordenadas
         * @param coor: coordenadas
         */
        Coordinate(sf::Vector2f coor);
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
        
        bool operator ==(const Coordinate &p) const;
        Coordinate operator +(const Coordinate &p) const;
        Coordinate operator +(const float &num) const;
        
        friend std::ostream& operator << (std::ostream &o,const Coordinate &p);
};

inline std::ostream& operator << (std::ostream &o,const Coordinate &p) {
    o << "(" << p.x << ", " << p.y << ")\n";
    return o;
}

#endif /* COORDINATE_H */
