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
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
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
    x = rect.top;
    y = rect.left;
    w = rect.width;
    h = rect.height;
}

template class Rect<int>;
template class Rect<float>;