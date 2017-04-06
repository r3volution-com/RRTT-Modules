#include <cstdlib>
#include <iostream>
#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //Prueba clase Game (Singleton)
    
    Game *p1 = Game::Instance();
    Game *p2 = p1->Instance();
    Game *p3 = Game::Instance();
    
    //Update, render, init, input
    
    cout << "Variable p1: " << p1 << "\n";
    cout << "Variable p2: " << p2 << "\n";
    cout << "Variable p3: " << p3 << "\n";
    
    return 0;
}

