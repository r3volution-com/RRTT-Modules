
#include <cstdlib>
#include "Game.h"

using namespace std;


int main(int argc, char** argv) {
    
    Game *game = Game::Instance();
    
    
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
        
        game->Input();
        
        game->Update();
    
        game->Render();
    
    }    
    
    return 0;
}

