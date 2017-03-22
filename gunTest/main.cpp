#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Player.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    Texture *tex = new Texture("resources/sprites.png");
    Player *rath = new Player(20, 20, 128, 128, 2.0f);
    rath->loadAnimation(tex, 0, 0, 3, 0.1f);
    Gun *weapon = new Gun();
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
        window.draw(rath->getAnimation()->getCurrentSprite());
        window.display();
        
    }
    return 0;
}