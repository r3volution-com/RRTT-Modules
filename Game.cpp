#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance(){
    
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::Game(){
    
    screenSize = new Coordinate(1280, 720);
    window = new sf::RenderWindow(sf::VideoMode(screenSize->x, screenSize->y), "Rath's Revenge: The Twisted Timeline");
    intro = new IntroState();
    menu = new MenuState();
    level = new LevelState();
    game = intro;
    
    iaSpeed = 4;
    fps = 60;
    iaps = fps/iaSpeed;
    
    fpsTimer = new Time(1);
}

void Game::Init(){
    fpsTimer->restart();
    game->Init();
}

void Game::Input(){
    
    game->Input();
    
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
        fpsTimer->restart();
        std::cout << "fps: " << fps << " iaps: " << iaps << "\n";
    }
    
    window->clear();
    
    game->Render();
    
    window->display();
    
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