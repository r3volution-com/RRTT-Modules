#ifndef INTERPOLATEDCOORDINATE_H
#define INTERPOLATEDCOORDINATE_H

#include <cstddef>
#include "Coordinate.h"

class InterpolatedCoordinate {
    private:
        Coordinate *act;
        Coordinate *last;
    public:
        InterpolatedCoordinate(float x, float y);
        InterpolatedCoordinate(Coordinate *firstCoord);
        virtual ~InterpolatedCoordinate();
        
        void setCoordinate(float x, float y);
        void setCoordinate(Coordinate *newCoord);
        
        Coordinate getCoordinate() { return *act; }
        Coordinate getIC();
};

#endif /* INTERPOLATEDCOORDINATE_H */