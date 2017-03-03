#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Entity.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    Texture *tex = new Texture("resources/map.png");
    
    Entity *rath = new Entity(10, 10, 128, 128, 0.5f);
    rath->loadAnimation(tex, 0, 0, 4, 0.1f);
    
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
            rath->move(0, -1);
            rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0, 1);
            rath->getAnimation()->changeSpriteRect(0, 256, 128, 128);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->move(-1, 0);
            rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            rath->getAnimation()->changeSpriteRect(0, 512, 128, 128);
        }
        //ToDo: Si no se pulsa ninguna tecla volver a idle
        
        window.clear();
        window.draw(rath->getAnimation()->getCurrentSprite());
        window.display();
        
    }
    return 0;
}

