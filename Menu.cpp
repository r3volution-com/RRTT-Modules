#include "Menu.h"
#include "Game.h"

Menu::Menu(Texture* bg, Texture *bLayout, Rect<float> *tRect, Font* bFont, int numButtons) {
    background = new Sprite(bg, Rect<float>(0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y)); //ToDo Sergio: tamaño sale del singleton
    buttonTextureRect = tRect;
    buttonLayout = bLayout;
    buttonFont = bFont;
    maxButtons = numButtons;
    buttons = new std::vector<Button*>();
}

Menu::~Menu() {
    delete background;
    delete buttonTextureRect;
    delete buttons; 
    background = NULL;
    buttonTextureRect = NULL;
    buttons = NULL;
}

bool Menu::addButton(Coordinate position, std::string text, sf::Color color, sf::Color outlineColor, int size){
    if (buttons->size() < maxButtons){
        Button *button = new Button(position, buttonLayout, *buttonTextureRect);
        button->setText(text, color, outlineColor, buttonFont, size);
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
    window->draw(*background->getSprite());
    for (int i = 0; i<buttons->size(); i++){
        buttons->at(i)->draw(window);
    }  
}
