#include "Rect.h"

template <class T>
Rect<T>::Rect(T rX, T rY, T rW, T rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
Rect<T>::Rect(sf::Rect<T> rect){
    x = rect.left;
    y = rect.top;
    w = rect.width;
    h = rect.height;
}

template <class T>
Rect<T>::Rect(const Rect<T>& rect) {
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

template <class T>
Rect<T>::~Rect() {
    
}

template <class T>
void Rect<T>::setRect(T rX, T rY, T rW, T rH){
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
void Rect<T>::setRect(sf::Rect<T> rect){
    x = rect.left;
    y = rect.top;
    w = rect.width;
    h = rect.height;
}

template class Rect<int>;
template class Rect<float>;