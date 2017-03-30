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
        Texture *buttonLayout;
        Rect<float> *buttonTextureRect;
        std::vector<Button*> *buttons; 
        Font *buttonFont;
        
        int maxButtons;
    public:
        Menu(Texture *bg, Texture *bLayout, Rect<float> *tRect, Font* bFont, int numButtons);
        virtual ~Menu();
        
        bool addButton(Coordinate position, std::string text, sf::Color color, sf::Color outlineColor, int size);
        
        void checkHover(Hitbox* mouse);
        int checkClicks();
        
        void drawMenu(sf::RenderWindow *window); //ToDo Sergio: mejorar usando singleton
};

#endif /* MENU_H */