#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../libs/Sprite.h"
#include "../../HUD.h"
#include "../../libs/Coordinate.h"
#include "../../libs/Rect.h"
#include "../../libs/Time.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: HUD Test");
    
    //Texture
    Texture *tex = new Texture("resources/sprites_hud.png");
    Texture *tex1 = new Texture("resources/background.png");
    Texture *tex2 = new Texture("resources/hud.png");
    
    //Font
    Font *f = new Font("resources/font.ttf");
    
    //Guns ON
    
    int activeGun = 0;
    
    
    int lifePlayer = 100;
    
    //Boss
    int lifeBoss = 150;
    
    //HUD
    Time *cF = new Time(); 
    HUD *hud = new HUD(tex1, tex2, tex, f, cF);
    hud->setFlashSprites(tex, tex);
    hud->setSpriteGuns(tex);
    
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
                case sf::Event::MouseWheelMoved:
                    if(event.mouseWheel.delta < 0){
                        activeGun = 0;
                    } else if(event.mouseWheel.delta > 0){
                        activeGun = 1;
                    }
                    break;
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            activeGun = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            activeGun = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
            if(lifePlayer < 100){
                lifePlayer = lifePlayer + 1;
                hud->changeLifePlayer(lifePlayer);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
            if(lifePlayer > 0){
                lifePlayer = lifePlayer - 1;
                hud->changeLifePlayer(lifePlayer);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)){
            if(lifeBoss < 150){
                lifeBoss = lifeBoss + 1;
                hud->changeLifeBoss(lifeBoss);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)){
            if(lifeBoss > 0){
                lifeBoss = lifeBoss - 1;
                hud->changeLifeBoss(lifeBoss);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
            hud->resetClockFlash();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            hud->resetClock();
        }
        
        
        hud->changeActiveGun(activeGun);        

        window->clear();
        
        hud->drawHUD(window);
        hud->drawFlashCooldown(window);
        hud->drawGunCooldown(window);
        hud->setTextLifePlayer();
        
        window->display();
        
    }
    return 0;
}

