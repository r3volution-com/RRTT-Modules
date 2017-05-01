/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pablo
 *
 * Created on 27 de marzo de 2017, 18:26
 */

#include <cstdlib>
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
    
        Game *game = Game::Instance();
        game->Init();
        //game->window->setFramerateLimit(20);
        while (game->window->isOpen()) {
        if(game->iaTimer->isExpired() == true){
            game->Input();
            game->Update();
            game->iaTimer->restart();
            game->currentTime = 1.0f/game->iaPS;
        }
        game->Render();
    }
}

