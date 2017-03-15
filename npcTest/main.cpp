#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "../Animation.h"
#include "../Player.h"
#include "../NPC.h"


int main(int argc, char** argv) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "RRTT: NPC Test");
    Texture *tex = new Texture("resources/sprites.png");
    
    Player *rath = new Player(0, 0, 128, 128, 2);
    rath->loadAnimation(tex, 0, 0, 4, 0.1f);
    
    
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
            rath->getAnimation()->move(0,-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->getAnimation()->move(0,1);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->getAnimation()->move(-1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->getAnimation()->move(1,0);
        }
     
        
        window->clear();
        window->draw(rath->getAnimation()->getCurrentSprite());
        window->display();
        
    }
    return 0;
}

