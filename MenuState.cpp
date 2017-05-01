#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() {
    
}

MenuState::~MenuState(){
    
}

void MenuState::Init(){
    Game *game = Game::Instance();
    game->rM->loadTexture("menu-background", "resources/menu-bg.png");
    game->rM->loadTexture("button-layout", "resources/button-layout.png");
    game->rM->loadFont("menu", "resources/font.ttf");
    principal = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("button-layout"), new Rect<float>(0,0,200,50), game->rM->getFont("menu"));
    principal->addButton(Coordinate (540,200), "Jugar", sf::Color::Black, sf::Color::Transparent, 20);
    principal->addButton(Coordinate (540,270), "Opciones", sf::Color::Black, sf::Color::Transparent, 20);
    principal->addButton(Coordinate (540,340), "Salir", sf::Color::Black, sf::Color::Transparent, 20);
    game->iM->addAction("click", thor::Action(sf::Mouse::Left));
    
}

void MenuState::Input(){
    if (Game::Instance()->iM->isActive("click")){
        int clicks = principal->checkClicks();
        switch (clicks){
            case 0:
                Game::Instance()->ChangeCurrentState("level");
            break;
            case 1:
                //Salir
            break;
            default: break;
        }
    }
}

void MenuState::Update(){
    principal->checkHover(Game::Instance()->mouse);
    
}

void MenuState::Render(){
    principal->drawMenu();
}

void MenuState::CleanUp(){
    
}