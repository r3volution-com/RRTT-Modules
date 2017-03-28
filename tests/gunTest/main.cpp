#include <cstdlib>
#include "../Gun.h"
#include "../Player.h"

int main(int argc, char** argv) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "RRTT: Gun Test");
    Texture *tex = new Texture("resources/sprites.png");
    Animation *scytheAnimation = new Animation(tex, 20, 20, 0, 0, 2, 0.2f);
    Gun *scythe = new Gun(0, 0, 20, 20, scytheAnimation);
    Player *rath = new Player(0, 0, 128, 128, 2);
    rath->setWeapon(scythe);
    rath->loadAnimation(tex, 0, 0, 3, 0.1f);
    
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
     
        window->clear();
        window->draw(rath->getAnimation()->getCurrentSprite());
        window->draw(scythe->getAnimation()->getCurrentSprite());
        window->display();
    }
    return 0;
}