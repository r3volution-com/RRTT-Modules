#include "Menu.h"

Menu::Menu(Sprite* bg, Sprite *bLayout, Font* bFont, int numButtons) {
    addedButtons = 0;
    background = bg;
    buttonLayout = bLayout;
    buttonFont = bFont;
    //buttons = new std::vector<Button>(numButtons);
}

Menu::~Menu() {
}

bool Menu::addButton(std::string text, float x, float y, int w, int h){
    if (addedButtons < maxButtons){
        Button *button = new Button(text, x, y, w, h, buttonLayout);
        //buttons->insert(addedButtons, button);
        addedButtons++;
        return true;
    } else return false;
}

void Menu::checkHover(Hitbox* mouse) {
    for (int i=0; i<addedButtons; i++){
        //buttons[i]->hover(mouse);
    }
}
int Menu::checkClicks() {
    for (int i=0; i<addedButtons; i++){
        //if (buttons[i]->getHover()) return i;
    }
    return -1;
}

void Menu::drawMenu(sf::RenderWindow *window){
    window->draw(background->getSprite());
    for (int i = 0; i<addedButtons; i++){
        window->draw(buttons[i]->getSprite());
    }
}