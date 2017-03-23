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
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: NPC Test");
    Font *font = new Font("resources/font.ttf");
    
    //Background
    Texture *tex0 = new Texture("resources/pyramid-background.jpg");
    Sprite *background = new Sprite(tex0, 1280, 720, 0, 0);
    //Player
    Texture *tex1 = new Texture("resources/white.png");
    Sprite *plHP = new Sprite(tex1, 100, 15, 0, 0);
    Sprite *bHP = new Sprite(tex1, 100, 20, 0, 0);
    plHP->move(150.0f,10.0f);
    bHP->move(590.0f,680.0f);
    //Textbox
    Texture *tex2 = new Texture("resources/textbox.png");
    Sprite *sp = new Sprite(tex2, 1280, 300, 0, 0);
    //HUD
    HUD *hud = new HUD(background, plHP, bHP);
    hud->setTextLayer(0, 420, sp, font);
    hud->setTLayerTextParams(16, sf::Color::Black, sf::Color::White);
    //Player
    Texture *tex = new Texture("resources/sprites.png");
    Player *rath = new Player(0, 0, 128, 128, 2);
    rath->loadAnimation(tex, 0, 0, 3, 0.1f);
    
    NPC *aldeano = new NPC(200, 200, 128, 128, 2, "Jose");
    aldeano->loadAnimation(tex, 0, 128, 3, 0.1f);
    aldeano->addSentence("probamos con esto\n\nPulsa espacio para continuar", 20, 520);
    aldeano->addSentence("probamos con esto otra ves\n\nPulsa espacio para continuar", 20, 520);
    aldeano->addSentence("probamos con esto por ultima vez\n\nPulsa espacio para continuar", 20, 520);
    
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
                        case sf::Keyboard::E:
                            if (rath->collision(aldeano->getHitbox()) && !showText){
                                showText = true;
                                aldeano->nextSentence();
                                hud->setTLayerTalker(aldeano->getName(), 1140, 440);
                                hud->setTLayerText(aldeano->getCurrentSentenceText(), aldeano->getCurrentSentencePosition()->x, aldeano->getCurrentSentencePosition()->y);
                            }
                            break;
                        case sf::Keyboard::Space:
                            if (showText){
                                if (!aldeano->nextSentence()) showText = false;
                                else hud->setTLayerText(aldeano->getCurrentSentenceText(), aldeano->getCurrentSentencePosition()->x, aldeano->getCurrentSentencePosition()->y);
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
     
        window->clear();
        window->draw(rath->getAnimation()->getCurrentSprite());
        window->draw(aldeano->getAnimation()->getCurrentSprite());
        if (showText) {
            hud->drawTextLayer(window);
        }
        window->display();
    }
    return 0;
}

