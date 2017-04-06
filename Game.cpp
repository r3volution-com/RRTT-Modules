#include "Game.h"
#include "GameState.h"

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
    game = intro;
    
}

void Game::Update(){
    
    game->Update();
    
}

void Game::Render(){
    
    game->Render();
    
}

void Game::Input(){
    
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