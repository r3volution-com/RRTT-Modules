#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "../Font.h"
#include "../Sprite.h"
#include "../Animation.h"
#include "../Player.h"
#include "../NPC.h"
#include "../HUD.h"


int main(int argc, char** argv) {
    bool showText = false;
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "RRTT: NPC Test");
    Font *font = new Font("resources/font.ttf");
    Texture *tex = new Texture("resources/sprites.png");
    
    Player *rath = new Player(0, 0, 128, 128, 2);
    rath->loadAnimation(tex, 0, 0, 3, 0.1f);
    
    NPC *aldeano = new NPC(200, 200, 128, 128, 2);
    //aldeano->setTextParams(font, 15, sf::Color::Black, sf::Color::White);
    aldeano->loadAnimation(tex, 0, 128, 3, 0.1f);
    aldeano->addSentence("probamos con esto\n\nPulsa espacio para continuar", 20, 340);
    aldeano->addSentence("probamos con esto otra ves\n\nPulsa espacio para continuar", 20, 340);
    aldeano->addSentence("probamos con esto por ultima vez\n\nPulsa espacio para continuar", 20, 340);
    
    Texture *tex2 = new Texture("resources/textbox.png");
    Sprite *sp = new Sprite(tex2, 640, 190, 0, 0);
    sp->move(0,290);
    
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
                        case sf::Keyboard::Space:
                            if (showText){
                                if (!aldeano->nextSentence()) showText = false;
                            }
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
     
        if (rath->collision(aldeano->getHitbox()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !showText){
            showText = true;
            aldeano->nextSentence();
            // setTLayerText(sentences->at(currentSentence), sentencePosition->at(currentSentence)->x, sentencePosition->at(currentSentence)->y);
        //ToDo: cambia la frase en HUD
        }
        
        window->clear();
        window->draw(rath->getAnimation()->getCurrentSprite());
        window->draw(aldeano->getAnimation()->getCurrentSprite());
        if (showText) {
            window->draw(sp->getSprite());
            window->draw(*aldeano->getCurrentSentence()->getText());
        }
        window->display();
    }
    return 0;
}

