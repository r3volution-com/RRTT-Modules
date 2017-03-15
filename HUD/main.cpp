#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite.h"
#include "../HUD.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: HUD Test");
    
    //Guns ON
    Texture *tex0 = new Texture("resources/homer.gif");
    Sprite *gun1 = new Sprite(tex0, 100, 100, 0, 0);
    Texture *tex1 = new Texture("resources/lenny.gif");
    Sprite *gun2 = new Sprite(tex1, 100, 100, 0, 0);
    gun2->move(0.0f,100.0f);
    /*Texture *tex3 = new Texture("resources/jake.jpg");
    Sprite *gun3 = new Sprite(tex3, 100, 100, 0, 0);
    gun3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *guns = new std::vector<Sprite*>();
    guns->push_back(gun1);
    guns->push_back(gun2);
    //guns->push_back(gun3);
    
    int activeGun = 0;
    
    //Guns Off
    Texture *tex4 = new Texture("resources/white.png");
    Sprite *go1 = new Sprite(tex4, 100, 100, 0, 0);
    Sprite *go2 = new Sprite(tex4, 100, 100, 0, 0);
    go2->move(0.0f,100.0f);
    /*Texture *tex6 = new Texture("resources/white.png");
    Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsO = new std::vector<Sprite*>();
    gsO->push_back(go1);
    gsO->push_back(go2);
    //gsO->push_back(go3);
    
    //Background
    Texture *tex7 = new Texture("resources/pyramid-background.jpg");
    Sprite *background = new Sprite(tex7, 1920, 1024, 0, 0);
    
    //Player
    Sprite *plHP = new Sprite(tex4,100 , 15, 0, 0);
    plHP->move(150.0f,10.0f);
    
    int maxLife = 100;
    int life = 100;
    
    //Boss
    Sprite *bHP = new Sprite(tex4,100 , 20, 0, 0);
    bHP->move(590.0f,680.0f);
    
    int maxLifeBoss = 150;
    int lifeBoss = 150;
    
    //Flash
    Sprite *fC = new Sprite(tex4,100 , 100, 0, 0);
    
    //HUD
    HUD *hud = new HUD(background, guns, gsO, plHP, bHP, fC);
    
    
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            activeGun = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            activeGun = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
            if(life < maxLife){
                life = life + 1;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
            if(life > 0){
                life = life - 1;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)){
            if(lifeBoss < maxLifeBoss){
                lifeBoss = lifeBoss + 1;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)){
            if(lifeBoss > 0){
                lifeBoss = lifeBoss - 1;
            }
        }
        
        hud->changeActiveGun(activeGun);
     
        
        window->clear();
        hud->drawHUD(window, maxLife, life, maxLifeBoss, lifeBoss);
        window->display();
        
    }
    return 0;
}

