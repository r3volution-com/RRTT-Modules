#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "../Sprite.h"
#include "../Player.h"
#include "../Cristales.h"

using namespace std;

int main(int argc, char** argv) {    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: Crystal Test");
    
    Texture *tex = new Texture("resources/Crystal.png");
    Texture *tex3 = new Texture("resources/sprites.png");

    Player *rath = new Player(new Rect<float>(0, 0, 128, 128), 2);
    rath->loadAnimation(tex3, new Coordinate(0, 0), 3, 0.1f);
    
    Crystals *crystal = new Cristal(tex, new Rect<float>(0, 0, 64, 60));
    crystal->setPosition(new Coordinate(350, 150));
    
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
        if(!cystal->getTouched()){
            window->draw(*crystal->getCrystalSprite()->getSprite());
        }
        window->draw(rath->getAnimation()->getCurrentSprite());
        window->display();
    }
    return 0;
}