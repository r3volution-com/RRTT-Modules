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
        
        bool h;
    public:
        float bX, bY;
        int bW, bH;
        
        Button(float x, float y, int w, int h, Sprite *bL);
        virtual ~Button();
        
        void setText(std::string t, sf::Color color, sf::Color outlineColor, Font *f, int size);
        void hover(Hitbox *mouse);
        bool getHover() { return h; }
        void draw(sf::RenderWindow *window);
        
};

#endif /* BUTTON_H */