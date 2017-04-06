#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {

    Game *p1 = Game::Instance();
    
    while (p1->window->isOpen()){
        
        p1->Input();
        
        p1->Update();
        
        p1->Render();
        
        std::cout << p1->fps << " " << p1->iaps << " ";
    }
    return 0;
}