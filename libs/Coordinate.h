#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
    private:

    public:
        float x, y;
        
        Coordinate(float xC, float yC);
        Coordinate(const Coordinate& coor);
        virtual ~Coordinate();
        
        void setCoordinate(float xC, float yC);
        void setCoordinate(Coordinate coor);
};

#endif /* COORDINATE_H */