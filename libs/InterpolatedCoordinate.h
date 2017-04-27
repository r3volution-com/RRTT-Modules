#ifndef INTERPOLATEDCOORDINATE_H
#define INTERPOLATEDCOORDINATE_H

#include <cstdlib>
#include "Coordinate.h"

class InterpolatedCoordinate {
    private:
        Coordinate *last;
        Coordinate *act;
        Coordinate *next;
    public:
        InterpolatedCoordinate(float x, float y);
        InterpolatedCoordinate(Coordinate firstCoord);
        virtual ~InterpolatedCoordinate();
        
        void setCoordinate(float x, float y);
        void setCoordinate(Coordinate newCoord);
        
        void move(float x, float y);
        void move(Coordinate newCoord);
        
        bool areEquals(float a, float b);
        
        Coordinate *getCoordinate() { return act; }
        Coordinate *getLastCoordinate() { return last; }
        Coordinate *getNextCoordinate() { return last; }
        Coordinate getIC();
};

#endif /* INTERPOLATEDCOORDINATE_H */