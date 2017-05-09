#include "Pie.h"
#include "../Game.h"

#include <iostream>

Pie::Pie(float radius, int resolution, int rotationAngle) {
    assert(radius > 0.f);
    shape = new thor::ConcaveShape();
    shape->setPointCount(resolution+1);
    
    pieRadius = radius;
    nbTotalPoints = resolution;
    pieIndex = 0;
    actualAngle = static_cast<unsigned int>(rotationAngle / 360.f * nbTotalPoints);
    if (radius > 0) {
        shape->setPoint(pieIndex, sf::Vector2f(0.f, 0.f));
        pieIndex++;
    }
}
Pie::Pie(){
    shape = new thor::ConcaveShape();
}

Pie::~Pie() {
    delete shape;
    shape = NULL;
}

void Pie::setColor(const sf::Color& fillColor){
    shape->setFillColor(fillColor);
}

void Pie::setOutline(float outlineThickness, const sf::Color& outlineColor){
    shape->setOutlineThickness(outlineThickness);
    shape->setOutlineColor(outlineColor);
}

void Pie::setFilledAngle(int increment){
    increment = std::fmod(increment, 360.f);
    const unsigned int nbActualPoints = static_cast<unsigned int>(increment / 360.f * nbTotalPoints); //ToDo: no suma
    //std::cout << "Dentro: " << nbActualPoints+pieIndex << "<=" << nbTotalPoints << "\n";
    if (nbActualPoints+pieIndex <= nbTotalPoints+1){
        thor::PolarVector2<float> vector(pieRadius, 0.f);
        for (unsigned int i = actualAngle; i < (actualAngle+nbActualPoints); i++) {
            vector.phi = 360.f * i / nbTotalPoints;
            std::cout << pieIndex << ", " << vector.phi << "\n";
            shape->setPoint(pieIndex, vector);
            pieIndex++;
        }
    
        actualAngle += nbActualPoints;
        
        //if (actualAngle > 360) actualAngle=actualAngle-360;
    }
}
thor::ConcaveShape* Pie::getShape(){
    std::cout << "sale" << pieIndex << "\n";
    if (pieIndex >= 3) return shape;
    else return (thor::ConcaveShape*) new sf::ConvexShape();
}