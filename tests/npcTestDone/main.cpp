#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "../../libs/Font.h"
#include "../../libs/Sprite.h"
#include "../../libs/Animation.h"
#include "../../Player.h"
#include "../../NPC.h"
//#include "../../HUD.h"


int main(int argc, char** argv) {
    bool showText = false;
    
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: NPC Test");
    Font *font = new Font("resources/font.ttf");
    
    //Background
    Texture *bTex = new Texture("resources/pyramid-background.jpg");
    //Hud
    Texture *hTex = new Texture("resources/hud.png");
    //Player
    Texture *lTex = new Texture("resources/white.png");
    //Textbox
    Texture *tTex = new Texture("resources/textbox.png");
    //HUD
   // HUD *hud = new HUD(bTex, hTex, lTex, font);
    //hud->setTextLayer(Coordinate (0,420), Rect<float>(0,0,1280,300), tTex);
    //hud->setTLayerTextParams(20, sf::Color::Black, sf::Color::White);
    //Player
    Texture *tex = new Texture("resources/sprites.png");
    Player *rath = new Player(Coordinate(0,0), tex, Rect<float>(0, 0, 128, 128), 2);
    rath->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
    //rath->loadAnimation(tex, Coordinate(0, 0), 3, 0.1f);
    
    NPC *aldeano = new NPC(Coordinate(200,200), tex, Rect<float>(200, 200, 128, 128), 2, "Jose");
    aldeano->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
    aldeano->getAnimation()->initAnimator();
    aldeano->getAnimation()->changeAnimation("idle", false);
    //aldeano->loadAnimation(tex, Coordinate(0, 128), 3, 0.1f);
    aldeano->addSentence("probamos con esto\n\nPulsa espacio para continuar", new Coordinate(20, 520));
    aldeano->addSentence("probamos con esto otra vez\n\nPulsa espacio para continuar", new Coordinate(20, 520));
    aldeano->addSentence("probamos con esto por ultima vez\n\nPulsa espacio para continuar", new Coordinate(20, 520));
    
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
                               // hud->setTLayerTalker(aldeano->getName(), 1140, 440);
                                //hud->setTLayerText(aldeano->getCurrentSentenceText(), aldeano->getCurrentSentencePosition()->x, aldeano->getCurrentSentencePosition()->y);
                            }
                            break;
                        case sf::Keyboard::Space:
                            if (showText){
                                //if (!aldeano->nextSentence()) showText = false;
                                //else hud->setTLayerText(aldeano->getCurrentSentenceText(), aldeano->getCurrentSentencePosition()->x, aldeano->getCurrentSentencePosition()->y);
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
        rath->getAnimation()->updateAnimator();
        aldeano->getAnimation()->updateAnimator();
        window->clear();
        window->draw(*rath->getAnimation()->getSprite());
        window->draw(*aldeano->getAnimation()->getSprite());
        if (showText) {
            //hud->drawTextLayer(window);
        }
        window->display();
    }
    return 0;
}

