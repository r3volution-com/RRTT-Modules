
#include <cstdlib>
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
    
    Game *game = Game::Instance();
    game->Init();
    clock->start();
    game->window->setFramerateLimit(150);
    while (game->window->isOpen()) {
        if(clock->isExpired() == true){
            game->Input();
            game->Update();
            clock->restart();
        }
    
        game->Render();
    
    }    
    
    return 0;
}

