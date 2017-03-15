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
        
        Texture *tButton;
        Sprite *button;
        
        bool h;
    public:
        float bX, bY;
        int bW, bH;
        
        Button(std::string t, float x, float y, int w, int h, Sprite *bL);
        virtual ~Button();
        
        void hover(Hitbox *mouse);
        bool getHover() { return h; }
        
        Sprite *getSprite();
        //void callFunction()
};

#endif /* BUTTON_H */