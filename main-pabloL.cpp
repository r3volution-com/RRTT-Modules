
#include <cstdlib>
#include "Game.h"

using namespace std;


int main(int argc, char** argv) {
    
    Game *game = Game::Instance();
    Time clock = new Time(1.0f/game->iaps);
    
    
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

