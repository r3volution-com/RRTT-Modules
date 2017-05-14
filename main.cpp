#include <cstdlib>
#include "Game.h"

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
    return 0;
}