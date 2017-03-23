#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics/Rect.hpp>


class Rect {
    private:
    public:
        int x, y, w, h;
        
        Rect(int rX, int rY, int rW, int rH);
        Rect(sf::IntRect rect);
        virtual ~Rect();
        
        void setRect(int rX, int rY, int rW, int rH);
        void setRect(sf::IntRect rect);
        
        sf::Rect<int> getRect(){
            return sf::Rect<int>(x, y, w, h);
        }
};

#endif /* RECT_H */