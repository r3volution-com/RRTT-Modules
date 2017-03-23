#ifndef BUTTON_H
#define BUTTON_H

#include "Hitbox.h"
#include "Sprite.h"
#include "Text.h"

class Button {
    private:
        Text *text;
        Hitbox *hitbox;
        Sprite *buttonLayout;
        Rect *buttonData;
        
        bool isHover;
    public:
        Button(Coordinate *pos, Texture *bL, Rect *textureRect);
        virtual ~Button();
        
        void setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size);
        void hover(Hitbox *mouse);
        bool getHover() { return isHover; }
        void draw(sf::RenderWindow *window);
        
};

#endif /* BUTTON_H */