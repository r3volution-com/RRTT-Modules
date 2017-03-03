#include "Menu.h"

Menu::Menu(Sprite* bg, Sprite *bLayout[], int numButtons, int numSubmenus) {
    addedButtons = 0;
    addedSubmenus = 0;
    background = bg;
    buttonLayout = bLayout;
    buttons = new Button[numButtons];
    submenus = new Button[numSubmenus];
}

Menu::~Menu() {
}

bool Menu::addButton(std::string text, float x, float y, int w, int h){
    if (addedButtons < maxButtons){
        Button *button = new Button(text, x, y, w, h, buttonLayout);
        buttons[addedButtons] = button;
        addedButtons++;
        return true;
    } else return false;
}

bool Menu::addSubmenu(Menu *submenu){
    if (addedSubmenus < maxSubmenus){
        submenus[addedSubmenus] = submenu;
        addedSubmenus++;
        return true;
    } else return false;
}