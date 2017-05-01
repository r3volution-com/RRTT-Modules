#ifndef COORDINATE_H
#define COORDINATE_H

#include <SFML/System.hpp>
#include <ostream>

class Coordinate {
    private:

    public:
        float x, y;
        
        Coordinate(float xC, float yC);
        Coordinate(sf::Vector2i coor);
        Coordinate(sf::Vector2f coor);
        Coordinate(const Coordinate& coor);
        virtual ~Coordinate();
        
        void setCoordinate(float xC, float yC);
        void setCoordinate(Coordinate coor);
        
        bool operator ==(const Coordinate &p) const;
        
        friend std::ostream& operator << (std::ostream &o,const Coordinate &p);
};

inline std::ostream& operator << (std::ostream &o,const Coordinate &p) {
    o << "(" << p.x << ", " << p.y << ")\n";
    return o;
}

#endif /* COORDINATE_H */