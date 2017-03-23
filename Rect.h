#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics/Rect.hpp>

template <class T>
class Rect {
    private:
    public:
        T x, y, w, h;
        
        Rect(T rX, T rY, T rW, T rH);
        Rect(sf::Rect<T> rect);
        virtual ~Rect();
        
        void setRect(T rX, T rY, T rW, T rH);
        void setRect(sf::Rect<T> rect);
        
        sf::Rect<T> getRect(){
            return sf::Rect<T>(x, y, w, h);
        }
        sf::IntRect getIntRect(){
            return sf::IntRect(x, y, w, h);
        }
        sf::FloatRect getFloatRect(){
            return sf::IntRect(x, y, w, h);
        }
};

#endif /* RECT_H */