
#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H
#include "Coordinate.h"
#include <vector>
#include <iostream>

class Trigonometry {
public:
    Trigonometry();
    virtual ~Trigonometry();
    
    float angle(Coordinate *initial, Coordinate *end);
    float distance(Coordinate *initial, Coordinate *end);
    std::vector<float> distance(std::vector<Coordinate*> *initial, Coordinate *end);
    Coordinate* direction(Coordinate *initial, Coordinate *end);
    
private:
    
        float PI;
        float ang;
        float posI[2] = {0,0};
        float posF[2] = {0,0};
        
};

#endif /* TRIGONOMETRY_H */

