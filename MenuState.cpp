#include "MenuState.h"
#include "Game.h"

#include <sys/stat.h>
#include <unistd.h>

bool file_exists (const std::string& name) {
  return (access(name.c_str(), F_OK) != -1);
}

MenuState::MenuState() {
    
}

MenuState::~MenuState(){
    
}

void MenuState::Init(){
    Game *game = Game::Instance();
    
    /* CANCIONES Y SONIDOS */
    game->rM->loadMusic("Intro", "resources/sonidos/Inicio.ogg");
    game->rM->getMusic("Intro")->getMusic()->setLoop(true);
    game->rM->getMusic("Intro")->getMusic()->play();
    
    game->rM->loadTexture("menu-background", "resources/menu-bg.png");
    game->rM->loadFont("menu", "resources/menu.ttf");
    game->rM->loadTexture("loading-game", "resources/loading_game.png");
    
    
    principal = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(0,535,318,64), game->rM->getFont("menu"));
    principal->addButton(Coordinate (825,270), "Nueva partida", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    principal->addButton(Coordinate (825,340), "Opciones", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    principal->addButton(Coordinate (825,410), "Salir", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    if (file_exists("save.txt")) principal->addButton(Coordinate (825,200), "Continuar", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones = new Menu(game->rM->getTexture("menu-background"), game->rM->getTexture("gui-tileset"), new Rect<float>(0,535,318,64), game->rM->getFont("menu"));
    opciones->addButton(Coordinate (825,270), "Musica On/Off", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones->addButton(Coordinate (825,340), "FX On/Off", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    opciones->addButton(Coordinate (825,410), "Volver", sf::Color::White, sf::Color(170, 170, 170, 255), 20);
    
    game->iM->addAction("click", thor::Action(sf::Mouse::Left));
    
    menuactual = 0;
    actual = principal;
    
    loading = new Sprite(game->rM->getTexture("loading-game"), Rect<float>(0,0,1280,720));
    loadTime = new Time(5.0f);
    
    loaded = false;
}

void MenuState::Input(){
    if (Game::Instance()->iM->isActive("click")){
        int clicks = actual->checkClicks();
        if (menuactual == 0){
            switch (clicks){
                case 0:
                    if(remove("save.txt") != 0) std::cerr << "No existe\n";
                    loadTime->start();
                    loaded = true;
                break;
                case 1:
                    Game::Instance()->rM->getSound("menu")->getSound()->play();
                    menuactual = 1;
                    actual = opciones;
                break;
                case 2:
                    Game::Instance()->window->close();
                break;
                case 3:
                    loadTime->start();
                    loaded = true;
                break;
                default: break;
            }
        } else if (menuactual == 1){
             switch (clicks){
                case 0:
                    Game::Instance()->rM->getSound("menu")->getSound()->play();
                break;
                case 1:
                    Game::Instance()->rM->getSound("menu")->getSound()->play();                    
                break;
                case 2:
                    Game::Instance()->rM->getSound("menu")->getSound()->play();                    
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
    if(loadTime->isExpired()){
        loaded = false;
        Game::Instance()->rM->getMusic("Intro")->getMusic()->stop();
        Game::Instance()->ChangeCurrentState("level");
        Game::Instance()->rM->getMusic("Main")->getMusic()->play();
    }
}

void MenuState::Render(){
    actual->drawMenu();
    if(loaded == true){
        Game::Instance()->window->draw(*loading->getSprite());
    }
}

void MenuState::CleanUp(){
    Game::Instance()->rM->releaseTexture("menu-background");
    Game::Instance()->rM->releaseTexture("loading-game");
    Game::Instance()->rM->releaseFont("menu");
    Game::Instance()->rM->releaseMusic("Intro");
    delete principal;
    delete loading;
    delete loadTime;
    principal = NULL;
    loading = NULL;
    loadTime = NULL;
}
