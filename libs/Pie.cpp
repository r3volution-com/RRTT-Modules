#include "Pie.h"
#include "../Game.h"

#include <iostream>

Pie::Pie(float radius, int resolution, int rotationAngle) {
    assert(radius > 0.f);
    pieRadius = radius;
    pieTotalPoints = resolution;
    pieFilledPoints = 0;

    shape = new thor::ConcaveShape();
    shape->setPointCount(0);
    
    addPoint(sf::Vector2f(0.f, 0.f));
    
    shape->setRotation(rotationAngle);
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

void Pie::addPoint(sf::Vector2f vector){
    const unsigned int size = shape->getPointCount();
    
    shape->setPointCount(size + 1);
    shape->setPoint(size, vector);
}

void Pie::setFilledAngle(int increment){
    increment = std::fmod(increment, 360.f);

    const unsigned int pieNewPoints = static_cast<unsigned int>(increment / 360.f * pieTotalPoints);
    
    if (pieFilledPoints+pieNewPoints <= pieTotalPoints){
        thor::PolarVector2<float> vector(pieRadius, 0.f);
        for (unsigned int i = 0; i < pieNewPoints; ++i) {
            vector.phi = 360.f * (i+pieFilledPoints) / pieTotalPoints;
            addPoint(vector);
        }
    }
    
    pieFilledPoints += pieNewPoints;
}

thor::ConcaveShape* Pie::getShape(){
    return shape;
}