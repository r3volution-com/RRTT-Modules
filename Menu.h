#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Sprite.h"
#include "Menu.h"
#include "Button.h"

class Menu {
    private:
        Sprite *background;
        Sprite *buttonLayout[];
        Menu   *submenus[];
        Button *buttons[];
        
        int addedButtons, maxButtons;
        int addedSubmenus, maxSubmenus;
    public:
        Menu(Sprite *bg, Sprite *bLayout[], int numButtons, int numSubmenus);
        virtual ~Menu();
        
        bool addButton(std::string text, float x, float y, int w, int h);
        bool addSubmenu(Menu *submenu);
};

#endif /* MENU_H */