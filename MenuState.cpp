#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() {
    
}

MenuState::~MenuState(){
    delete principal;

    principal = NULL;
}

void MenuState::Init(){
    Game *game = Game::Instance();
    //musica.openFromFile("resources/Inicio.ogg");
    //musica.setLoop(true);
    //musica.play();
    game->rM->loadTexture("menu-background", "resources/menu-bg.png");
    game->rM->loadFont("menu", "resources/font.ttf");
    principal = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(513,925,200,50), game->rM->getFont("menu"));
    principal->addButton(Coordinate (770,270), "Jugar", sf::Color::Black, sf::Color::Transparent, 20);
    principal->addButton(Coordinate (770,340), "Opciones", sf::Color::Black, sf::Color::Transparent, 20);
    principal->addButton(Coordinate (770,410), "Salir", sf::Color::Black, sf::Color::Transparent, 20);
    opciones = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(513,925,200,50), game->rM->getFont("menu"));
    opciones->addButton(Coordinate (770,270), "Musica On/Off", sf::Color::Black, sf::Color::Transparent, 20);
    opciones->addButton(Coordinate (770,340), "FX On/Off", sf::Color::Black, sf::Color::Transparent, 20);
    opciones->addButton(Coordinate (770,410), "Volver", sf::Color::Black, sf::Color::Transparent, 20);
    game->iM->addAction("click", thor::Action(sf::Mouse::Left));
    
    menuactual = 0;
    actual = principal;
}

void MenuState::Input(){
    if (Game::Instance()->iM->isActive("click")){
        int clicks = actual->checkClicks();
        if (menuactual == 0){
            switch (clicks){
                case 0:
                    //musica.stop();
                    Game::Instance()->ChangeCurrentState("level");
                break;
                case 1:
                    menuactual = 1;
                    actual = opciones;
                break;
                case 2:
                    Game::Instance()->window->close();
                break;
                default: break;
            }
        } else if (menuactual == 1){
             switch (clicks){
                case 0:
                    
                break;
                case 1:
                    
                break;
                case 2:
                    menuactual = 0;
                    actual = principal;
                break;
                default: break;
            }
        }
    }
}

void MenuState::Update(){
    actual->checkHover(Game::Instance()->mouse);
}

void MenuState::Render(){
    actual->drawMenu();
}

void MenuState::CleanUp(){
    Game::Instance()->rM->releaseTexture("menu-background");
    Game::Instance()->rM->releaseFont("menu");
    delete principal;
    principal = NULL;
}