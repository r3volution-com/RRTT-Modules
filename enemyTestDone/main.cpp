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
#include "../Enemy.h"

using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    Texture *text = new Texture("resources/sprites.png");
    Enemy *enemy= new Enemy(new Rect<float> (320, 240, 128, 128), 1.0f);
    enemy->loadAnimation(text, new Coordinate(0,0), 3, 0.5f);
    window.setFramerateLimit(120);
    
    //Bucle del juego
    while (window.isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                default: break;
            }
        }
        
        
        
        window.clear();
        window.draw(enemy->getAnimation()->getCurrentSprite());
        window.display();
    }
    return 0;
}

