#include "Rect.h"

Rect::Rect(float rX, float rY, float rW, float rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}
Rect::Rect(sf::FloatRect rect){
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
}

Rect::Rect(sf::IntRect rect){
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
}

Rect::~Rect() {
    
}
void Rect::setRect(float rX, float rY, float rW, float rH){
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}
void Rect::setRect(sf::FloatRect rect){
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
}

void Rect::setRect(sf::IntRect rect){
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
}