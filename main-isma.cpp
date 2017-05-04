#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "libs/Sprite.h"
#include "Player.h"
#include "Game.h"
#include "Crystals.h"

using namespace std;

int main(int argc, char** argv) {
    
    
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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0,-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0,1);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->move(-1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1,0);
        }
     
        if (rath->collision(crystal->getHitbox())){
            crystal->setTouched();
        }
        
        window->clear();
        if(!crystal->getTouched()){
            window->draw(*crystal->getCrystalSprite()->getSprite());
        }
        window->draw(*rath->getAnimation()->getSprite());
        window->display();
    }
    return 0;
}