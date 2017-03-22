#include "Rect.h"

Rect::Rect(int rX, int rY, int rW, int rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}
Rect::Rect(sf::IntRect *rect){
    x = rect->top;
    y = rect->left;
    w = rect->width;
    h = rect->height;
}
Rect::~Rect() {
    
}
void Rect::setRect(int rX, int rY, int rW, int rH){
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}
void Rect::setRect(sf::IntRect *rect){
    x = rect->top;
    y = rect->left;
    w = rect->width;
    h = rect->height;
}