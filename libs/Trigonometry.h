
#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H
#include "Coordinate.h"
#include <vector>
#include <iostream>

class Trigonometry {
public:
    Trigonometry();
    virtual ~Trigonometry();
    
    /**
     * Calcula el angulo
     * @param initial: Coordenada inicial Tipo Coordinate
     * @param end: Coordenada final Tipo Coordinate
     * @return 
     */
    float angle(Coordinate initial, Coordinate end);
    
    float angleWindow(Coordinate end);
    /**
     * Calcula la distancia
     * @param initial: Distancia inicial, Tipo Coordinate
     * @param end: Distancia final, Tipo Coordinate
     * @return 
     */
    float distance(Coordinate initial, Coordinate end);
    std::vector<float> distance(std::vector<Coordinate> initial, Coordinate end);
    Coordinate direction(Coordinate initial, Coordinate end);
    
private:
    
        float PI;
        float ang;
        float posI[2] = {0,0};
        float posF[2] = {0,0};
        
};

#endif /* TRIGONOMETRY_H */

