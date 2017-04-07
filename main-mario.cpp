#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {

    Game *p1 = Game::Instance();
    
    while (p1->window->isOpen()){
        
        p1->Input();
        
        p1->Update();
        
        p1->Render();
        
        std::cout << "fps: " << p1->fps << " iaps: " << p1->iaps << "\n";
    }
    return 0;
}