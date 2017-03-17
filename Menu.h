#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Font.h"
#include "Hitbox.h"
#include "Sprite.h"
#include "Button.h"

class Menu {
    private:
        Sprite *background;
        Sprite *buttonLayout;
        std::vector<Button*> *buttons;
        Font *buttonFont;
        
        int maxButtons;
    public:
        Menu(Sprite *bg, Sprite *bLayout, Font* bFont, int numButtons);
        virtual ~Menu();
        
        bool addButton(std::string text, float x, float y, int w, int h, sf::Color color, sf::Color outlineColor, int size);
        
        void checkHover(Hitbox* mouse);
        int checkClicks();
        
        void drawMenu(sf::RenderWindow *window); //ToDo: mejorar usando singleton
};

#endif /* MENU_H */