#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance(){
    
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

void Game::Game(){
    
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Rath's Revenge: The Twisted Timeline");
    level = new Level();
    menu = new Menu();
    
}

void Game::Update(){
    
}

void Game::Render(){
    
    level->draw(window);
    menu->drawMenu(window);
    
}

void Game::Input(){
    
}

void Game::Init(){
    
}