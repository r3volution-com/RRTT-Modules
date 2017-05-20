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
        int pieTotalPoints;
        int pieFilledPoints;
        
        char direction;

        void addPoint(sf::Vector2f vector);
    public:
        Pie();
        Pie(float radius, int resolution, int rotationAngle);
        virtual ~Pie();
        
        void setColor(const sf::Color& fillColor);
        void setOutline(float outlineThickness, const sf::Color& outlineColor);
        
        void setFilledAngle(int increment);
        
        void setDirection(char d){ direction = d; }
        char getDirection(){ return direction; }
        
        int getFilledAngle() { return 360.f * pieFilledPoints / pieTotalPoints; }
        
        thor::ConcaveShape* getShape();
};

#endif /* PIE_H */