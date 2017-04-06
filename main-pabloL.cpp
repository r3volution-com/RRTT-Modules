
#include <cstdlib>
#include "Game.h"

using namespace std;


int main(int argc, char** argv) {
    
    Game *game = Game::Instance();
    
    
    while (window->isOpen()) {
        //Bucle de obtención de eventos
        
        
        game->Input();
        
        game->Update();
    
        game->Render();
    
    }    
    
    return 0;
}

