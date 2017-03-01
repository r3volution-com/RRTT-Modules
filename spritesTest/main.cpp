#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Protagonista.h"

using namespace sf;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    sf::Texture tex;
    //Cargo la imagen donde reside la textura del sprite
    if (!tex.loadFromFile("resources/map.png")) {
        std::cerr << "Error cargando la imagen map.png";
        exit(0);
    }
    
    Protagonista rath = Protagonista();
    
    window.setFramerateLimit(60);
    
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
        window.draw(rath.getSprite());
        window.display();
        
    }
    return 0;
}

