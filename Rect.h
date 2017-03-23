#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics/Rect.hpp>


class Rect {
    private:
    public:
        int x, y, w, h;
        
        Rect(float rX, float rY, float rW, float rH);
        Rect(sf::FloatRect rect);
        Rect(sf::IntRect rect);
        virtual ~Rect();
        
        void setRect(float rX, float rY, float rW, float rH);
        void setRect(sf::FloatRect rect);
        void setRect(sf::IntRect rect);
        
        sf::Rect<int> getRect(){
            return sf::Rect<int>(x, y, w, h);
        }
};

#endif /* RECT_H */