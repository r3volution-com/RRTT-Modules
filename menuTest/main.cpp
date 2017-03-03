#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    Texture *tex = new Texture("resources/map.png");
    Sprite *sp = new Sprite(tex, 128, 128, 0, 0);
    int w, h;
    w = h = 128;
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
     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            sp->move(0, -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            sp->move(0, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            w--;
            sp->setSize(w, h);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            h--;
            sp->setSize(w, h);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            w = h = 128;
            sp->restoreSize();
        }
        
        window.clear();
        window.draw(sp->getSprite());
        window.display();
        
    }
    return 0;
}

