#include "Menu.h"
#include "Game.h"

Menu::Menu(Texture* bg, Texture *bLayout, Rect<float> *tRect, Font* bFont) {
    background = new Sprite(bg, Rect<float>(0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    buttonTextureRect = tRect;
    buttonLayout = bLayout;
    buttonFont = bFont;
    buttons = new std::vector<Button*>();
}

Menu::~Menu() {
    delete background;
    delete buttonTextureRect;
    delete buttons; 
    
    /*Faltaria:
        - buttonFont -> Segmentation fault
     */
    
    background = NULL;
    buttonTextureRect = NULL;
    buttons = NULL;
}

void Menu::addButton(Coordinate position, std::string text, sf::Color color, sf::Color outlineColor, int size){
    Button *button = new Button(position, buttonLayout, *buttonTextureRect);
    button->setText(text, color, outlineColor, buttonFont, size);
    buttons->push_back(button);
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

void Menu::drawMenu(){
    Game::Instance()->window->draw(*background->getSprite());
    for (int i = 0; i<buttons->size(); i++){
        buttons->at(i)->draw();
    }  
}
