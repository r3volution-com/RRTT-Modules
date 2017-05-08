#include "Pie.h"
#include "../Game.h"

#include <iostream>

Pie::Pie(float radius, int resolution) {
    assert(radius > 0.f);
    shape = new thor::ConcaveShape();
    shape->setPointCount(resolution);
    pieRadius = radius;
    nbTotalPoints = resolution;
    pieFilled = 0;
    if (radius > 0) {
        shape->setPoint(0, sf::Vector2f(0.f, 0.f));
        pieFilled++;
    }
}

Pie::~Pie() {
}

void Pie::setColor(const sf::Color& fillColor){
    shape->setFillColor(fillColor);
}

void Pie::setOutline(float outlineThickness, const sf::Color& outlineColor){
    shape->setOutlineThickness(outlineThickness);
    shape->setOutlineColor(outlineColor);
}

void Pie::setFilledAngle(int angle){
    angle = std::fmod(angle, 360.f);
    const unsigned int nbActualPoints = static_cast<unsigned int>(angle / 360.f * nbTotalPoints); //ToDo: no suma

        //std::cout << nbActualPoints << " " << shape->getPointCount() << "\n";

    if (nbActualPoints+pieFilled <= nbTotalPoints){
        thor::PolarVector2<float> vector(pieRadius, 0.f);
        for (unsigned int i = pieFilled; i <= (pieFilled+nbActualPoints); ++i) {
            std::cout << i << "\n";
            vector.phi = 360.f * i / nbTotalPoints;

            shape->setPoint(i, vector);
        }
    
        pieFilled += nbActualPoints;
    }
}
thor::ConcaveShape* Pie::getShape(){
    if (pieFilled > 3) return shape;
    else return (thor::ConcaveShape*)new sf::ConvexShape();
}