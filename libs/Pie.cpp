#include "Pie.h"
#include "../Game.h"

#include <iostream>

Pie::Pie(float radius, int resolution, int rotationAngle) {
    pieRadius = radius;
    pieTotalPoints = resolution+1;
    pieIndex = 0;
    pieAngle = 0;
    
    if (radius > 0) {
        shape = new thor::ConcaveShape();
        shape->setPointCount(resolution); //+1 es por el por el punto central
        shape->setPoint(pieIndex, sf::Vector2f(0.f, 0.f));
        shape->setRotation(rotationAngle);
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
    int next = pieAngle+increment;
    std::cout << "if " << next << "<=" << pieTotalPoints << "\n";
    if (next <= pieTotalPoints){
        thor::PolarVector2<float> vector(pieRadius, 0.f);
        for (unsigned int i = pieAngle; i < next; i++) {
            int degrees = 360.f * i / (pieTotalPoints-1);
    std::cout << "degrees = 360.f*"<<i<<"/("<<pieTotalPoints<<"-1) = " << degrees << "\n";
            if (degrees > 360) degrees = 359;
            vector.phi = degrees;
    std::cout << "Insertando: " << pieIndex << " " << pieAngle << " " << vector.phi << "\n";
            shape->setPoint(pieIndex, vector);
            pieIndex++;
        }
        pieAngle+=increment;
    }
}

thor::ConcaveShape* Pie::getShape(){
    //std::cout << "Mostrando: " << pieIndex << "\n";
    if (pieIndex >= 3) return shape;
    else return (thor::ConcaveShape*) new sf::ConvexShape();
}