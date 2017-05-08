#ifndef PIE_H
#define PIE_H

#include <assert.h>
#include <cmath>
#include <Thor/Shapes.hpp>
#include <Thor/Vectors.hpp>

class Pie {
    private:
        thor::ConcaveShape *shape;
        int pieRadius;
        int nbTotalPoints; //40
        int pieFilled;
    public:
        Pie(float radius, int resolution);
        virtual ~Pie();
        
        void setColor(const sf::Color& fillColor);
        void setOutline(float outlineThickness, const sf::Color& outlineColor);
        
        void setFilledAngle(int angle);
        
        int getFilledAngle() { return pieFilled; }
        
        thor::ConcaveShape* getShape();
};

#endif /* PIE_H */