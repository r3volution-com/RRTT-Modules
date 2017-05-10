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
        /**
         * Crea el objeto coordenada interpolada
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        InterpolatedCoordinate(float x, float y);
        
        /**
         * Crea el objeto coordenada interpolada
         * @param firstCoord: Primera coordenada
         */
        InterpolatedCoordinate(Coordinate firstCoord);
        virtual ~InterpolatedCoordinate();
        
        /**
         * Establece las coordenadas
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setCoordinate(float x, float y);
        
        /**
         * Establece las coordenadas
         * @param newCoord: Coordenadas
         */
        void setCoordinate(Coordinate newCoord);
        
        /**
         * Desplazamiento
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void move(float x, float y);
        
        /**
         * Deplazamiento
         * @param newCoord: Coordenadas
         */
        void move(Coordinate newCoord);
        
        /**
         * Compruebe si las interpoladas son iguales
         * @param a: Una interpolada
         * @param b: Otra interpolada
         * @return 
         */
        bool areEquals(float a, float b);
        
        void update();
        
        Coordinate *getCoordinate() { return act; }
        Coordinate *getLastCoordinate() { return last; }
        Coordinate *getNextCoordinate() { return next; }
        Coordinate getIC();
};

#endif /* INTERPOLATEDCOORDINATE_H */