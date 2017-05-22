#include "Menu.h"
#include "Game.h"

Menu::Menu(Texture* bg, Texture *bLayout, Rect<float> *tRect, Font* bFont) {
    background = new Sprite(bg, Rect<float>(0, 0, Game::Instance()->screenSize->x, Game::Instance()->screenSize->y));
    buttonTextureRect = tRect;
    buttonLayout = bLayout;
    buttonFont = bFont;
}

Menu::~Menu() {
    delete background;
    delete buttonTextureRect;
    
    for (int i=0; i<buttons.size(); i++){
        delete buttons.at(i);
        buttons.at(i) = NULL;
    }
    buttons.clear();
    
    background = NULL;
    buttonTextureRect = NULL;
}

void Menu::addButton(Coordinate position, std::string text, sf::Color color, sf::Color outlineColor, int size){
    Button *button = new Button(position, buttonLayout, *buttonTextureRect);
    button->setText(text, color, buttonFont, size);
    button->setOutline(1, outlineColor, sf::Color::Transparent);
    buttons.push_back(button);
}

void Menu::checkHover(Hitbox* mouse) {
    for (int i=0; i<buttons.size(); i++){
        buttons.at(i)->hover(mouse);
    }
}
int Menu::checkClicks() {
    for (int i=0; i<buttons.size(); i++){
        if (buttons.at(i)->getHover()) return i;
    }
    return -1;
}

void Menu::drawMenu(){
    Game::Instance()->window->draw(*background->getSprite());
    for (int i = 0; i<buttons.size(); i++){
        buttons.at(i)->draw();
    }  
}
