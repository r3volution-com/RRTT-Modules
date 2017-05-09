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
        int pieIndex;
        int actualAngle;
    public:
        Pie();
        Pie(float radius, int resolution, int rotationAngle);
        virtual ~Pie();
        
        void setColor(const sf::Color& fillColor);
        void setOutline(float outlineThickness, const sf::Color& outlineColor);
        
        void setFilledAngle(int increment);
        
        int getFilledAngle() { return pieIndex; }
        
        thor::ConcaveShape* getShape();
};

#endif /* PIE_H */