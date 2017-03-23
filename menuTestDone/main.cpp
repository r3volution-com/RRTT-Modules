#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Rect.h"
#include "../Sprite.h"
#include "../Menu.h"

int main(int argc, char** argv) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "RRTT: Menu Test");
    
    Texture *tex = new Texture("resources/pyramid-background.jpg");
    Texture *tex2 = new Texture("resources/button-map.png");
    
    Font *fuente = new Font("resources/font.ttf");
    
    Menu *menu = new Menu(tex, tex2, new Rect<float>(0,0,120, 25), fuente, 1);
    if (!menu->addButton(new Coordinate(200,200), "hola", sf::Color::Black, sf::Color::White, 15)) window->close();
    
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    Hitbox *mouse = new Hitbox(pos.x, pos.y, 1, 1);

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
        pos = sf::Mouse::getPosition(*window);
        mouse->setPosition(pos.x, pos.y);
        menu->checkHover(mouse);
       
        window->clear();
        menu->drawMenu(window);
        window->display();
        
    }
    return 0;
}

