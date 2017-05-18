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
    
    /* CANCIONES */
    game->rM->loadMusic("Intro", "resources/Inicio.ogg");
    game->rM->getMusic("Intro")->getMusic()->setLoop(true);
    game->rM->getMusic("Intro")->getMusic()->play();
    
    game->rM->loadMusic("Main", "resources/main.ogg");
    game->rM->getMusic("Main")->getMusic()->setLoop(true);
    
    game->rM->loadTexture("menu-background", "resources/menu-bg.png");
    game->rM->loadFont("menu", "resources/menu.ttf");
    
    principal = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(511,925,200,64), game->rM->getFont("menu"));
    principal->addButton(Coordinate (825,270), "Jugar", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    principal->addButton(Coordinate (825,340), "Opciones", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    principal->addButton(Coordinate (825,410), "Salir", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(511,925,200,64), game->rM->getFont("menu"));
    opciones->addButton(Coordinate (825,270), "Musica On/Off", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones->addButton(Coordinate (825,340), "FX On/Off", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones->addButton(Coordinate (825,410), "Volver", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    
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
                    Game::Instance()->rM->getMusic("Intro")->getMusic()->stop();
                    Game::Instance()->ChangeCurrentState("level");
                    Game::Instance()->rM->getMusic("Main")->getMusic()->play();
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
    Game::Instance()->rM->releaseMusic("Intro");
    delete principal;
    principal = NULL;
}
