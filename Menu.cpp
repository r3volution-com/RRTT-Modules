#include "Menu.h"

Menu::Menu(Sprite* bg, Sprite *bLayout, Font* bFont, int numButtons) {
    background = bg;
    buttonLayout = bLayout;
    buttonFont = bFont;
    buttons = new std::vector<Button*>();
}

Menu::~Menu() {
}

bool Menu::addButton(std::string text, float x, float y, int w, int h){
    if (buttons->size() < maxButtons){
        Button *button = new Button(text, x, y, w, h, buttonLayout);
        buttons->push_back(button);
        return true;
    } else return false;
}

void Menu::checkHover(Hitbox* mouse) {
    for (int i=0; i<buttons->size(); i++){
        buttons->at(i)->hover(mouse);
    }
}
int Menu::checkClicks() {
    for (int i=0; i<buttons->size(); i++){
        if (buttons->at(i)->getHover()) return i;
    }
    return -1;
}

void Menu::drawMenu(sf::RenderWindow *window){
    window->draw(background->getSprite());
    for (int i = 0; i<buttons->size(); i++){
        window->draw(buttons->at(i)->getSprite()->getSprite());
    }  
}