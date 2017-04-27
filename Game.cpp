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
    game = level;
    
    clock = new Time(1.0f/game->iaSpeed);
    deltaTime = 0;
    
    rM = new ResourceManager();
    
    iM = new Event();
}

void Game::Init(){
    fpsTimer->start();
    iM->addAction("close", thor::Action(sf::Keyboard::Escape, thor::Action::ReleaseOnce) || thor::Action(sf::Event::Closed));
    game->Init();
    fpsTimer->start();
}

void Game::Input(){
    
    if (iM->isActive("close")) Game::Instance()->window->close();
    game->Input();
    
}

void Game::Update(){
    
    iM->update();
    game->Update();
    
}

void Game::Render(){
    deltaTime = fpsTimer->getTime()-currentTime;
    currentTime = fpsTimer->getTime();
    
    window->clear();
    
    game->Render();
    
    window->display();
}

void Game::ChangeCurrentState(const std::string &state){
    
    game->CleanUp();
    
    if(state == "level"){
        game = level;
    }else if(state == "menu"){
        game = menu;
    }else if(state == "intro"){
        game = intro;
    }
    game->Init();
}
