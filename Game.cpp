#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance(){
    
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::Game(){
    
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Rath's Revenge: The Twisted Timeline");
    level = new LevelState();
    menu = new MenuState();
    intro = new IntroState();
    game = intro;
    
    iaSpeed = 4;
    fps = 60;
    iaps = fps/iaSpeed;
    
    fpsTimer = new Time(1);
    fpsTimer->restart();
}

void Game::Update(){
    
    game->Update();
    
}

void Game::Render(){
    fpsCounter++;
    if (fpsTimer->isExpired()){
        fps = fpsCounter;
        iaps = fps/iaSpeed;
        fpsCounter = 0;
    }
    
    window->clear();
    
    game->Render();
    
    window->display();
    
}

void Game::Input(){
    
       sf::Event event;
        while (window->pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window->close();
                        break;
                        default:
                        break;
                    }
                break;
                default: break;
            }
        }
    
    game->Input();
    
}

void Game::ChangeCurrentState(const std::string &state){
    
    if(state == "level"){
        game = level;
    }else if(state == "menu"){
        game = menu;
    }else if(state == "intro"){
        game = intro;
    }
    
}