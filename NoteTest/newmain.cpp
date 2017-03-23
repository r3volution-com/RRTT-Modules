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
    bool taken = false;
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: Note Test");
    
    Font *font = new Font("resources/font.ttf");
    Texture *tex = new Texture("resources/Paper-Sprite.png");
    Texture *tex2 = new Texture("resources/pergamino.jpg");
    Texture *tex3 = new Texture("resources/sprites.png");
    Sprite *sp = new Sprite(tex, 64, 60, 0, 0);
    Sprite *sp2 = new Sprite(tex2, 608, 488, 0, 0);
    sp2->move(350, 150);
    Text *text =new Text("Hello World!", 650, 400, sf::Color::Black, font, 20);

    
    Player *rath = new Player(0, 0, 128, 128, 2);
    rath->loadAnimation(tex3, 0, 0, 3, 0.1f);
    
    Note *note = new Note(600, 350, 64, 60, sp, sp2);
    
    
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
            taken=true;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && showText){
            showText=false;
        }
        
        window->clear();
        if(taken==false){
            window->draw(note->getNoteSprite()->getSprite());
        }
        window->draw(rath->getAnimation()->getCurrentSprite());
        if (showText) {
            window->draw(note->getBackgroundSprite()->getSprite());
            window->draw(*text->getText());
        }
        window->display();
    }
    return 0;
}

