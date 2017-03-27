#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "../Font.h"
#include "../Sprite.h"
#include "../Player.h"
#include "../Note.h"
#include "../Text.h"

int main(int argc, char** argv) {
    bool showText = false;
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: Note Test");
    
    Font *font = new Font("resources/font.ttf");
    Texture *tex = new Texture("resources/Paper-Sprite.png");
    Texture *tex2 = new Texture("resources/pergamino.png");
    Texture *tex3 = new Texture("resources/sprites.png");

    Player *rath = new Player(new Rect<float>(0, 0, 128, 128), 2);
    rath->loadAnimation(tex3, new Coordinate(0, 0), 3, 0.1f);
    
    Note *note = new Note(tex, new Rect<float>(0, 0, 64, 60), tex2, new Rect<float>(0, 0, 608, 488), font);
    note->setPosition(new Coordinate(350, 150));
    note->setBackgroundPosition(new Coordinate(100, 100));
    note->setText("Hola mundo!", sf::Color::Black, sf::Color::White, 1, 25);
    
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
     
        if (rath->collision(note->getHitbox()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !showText){
            showText = true;
            note->setTaken();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && showText){
            showText=false;
        }
        
        window->clear();
        if(!note->getTaken()){
            window->draw(*note->getNoteSprite()->getSprite());
        }
        window->draw(rath->getAnimation()->getCurrentSprite());
        if (showText) {
            window->draw(*note->getBackgroundSprite()->getSprite());
            window->draw(*note->getText()->getText());
        }
        window->display();
    }
    return 0;
}

