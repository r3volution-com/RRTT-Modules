#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
    private:

    public:
        float x, y;
        
        Coordinate(float xC, float yC);
        virtual ~Coordinate();
        
        void setCoordinate(float xC, float yC);
};

#endif /* COORDINATE_H */