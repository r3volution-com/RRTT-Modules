#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "../Font.h"
#include "../Sprite.h"
#include "../Player.h"
#include "../Note.h"
#include "../Text.h"

int main(int argc, char** argv) {
    
    char dirH='I';
    char dirV='I';
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: Note Test");
    
    Texture *tex = new Texture("resources/sprites.png");
    
    Sprite *sp = new Sprite(tex, new Rect<float>(0,0, 64, 60));
    Player *rath = new Player(new Rect<float>(0,0,128, 128), 2);
    rath->loadAnimation(tex, new Coordinate(0,0),3, 0.1f); 
    rath->setFlashRange(10);
    
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
            dirV='U';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0,1);
            dirV='D';
        }
        else{
         dirV='I';   
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->move(-1,0);
            dirH='L';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1,0);
            dirH='R';
        }
        else{
         dirH='I';   
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)&&(dirH=='R')){
            rath->flash(1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)&&(dirV=='U')){
            rath->flash(0,-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)&&(dirV=='D')){
            rath->flash(0,1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)&&(dirH=='L')){
            rath->flash(-1,0);
        }
        
        
        
        window->clear();

        window->draw(rath->getAnimation()->getCurrentSprite());

        window->display();
    }
    return 0;
}