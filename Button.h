#ifndef BUTTON_H
#define BUTTON_H

#include "Text.h"
#include "Hitbox.h"
#include "Sprite.h"
#include "Rect.h"

class Button {
    private:
        Text *text;
        Hitbox *hitbox;
        Sprite *buttonLayout;
        Rect<float> *buttonData;
        
        bool isHover;
    public:
        Button(Coordinate pos, Texture *bL, Rect<float> textureRect);
        virtual ~Button();
        
        void setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size);
        void hover(Hitbox *mouse);
        bool getHover() { return isHover; }
        void draw(sf::RenderWindow *window);
        
        Sprite *getSprite() {return buttonLayout;}
        
};

#endif /* BUTTON_H */