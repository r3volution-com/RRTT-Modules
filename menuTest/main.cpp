#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite.h"
#include "../Menu.h"

int main(int argc, char** argv) {
    sf::RenderWindow *window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    
    Texture *tex = new Texture("resources/pyramid-background.png");
    Sprite *background = new Sprite(tex, 640, 480, 0, 0);
    Texture *tex2 = new Texture("resources/button-map.png");
    Sprite *buttons = new Sprite(tex2, 120, 25, 0, 0);
    Menu *menu = new Menu(background, buttons, 1);
    menu->addButton("hola", 200, 200, 120, 25);

    window->setFramerateLimit(120);
    
    //Bucle del juego
    while (window->isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window->pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window->close();
                        break;
                        default:
                        break;
                    }
                break;
                default: break;
            }
        }
     
        
        window->clear();
        menu->drawMenu(window);
        window->draw(sp->getSprite());
        window->display();
        
    }
    return 0;
}

