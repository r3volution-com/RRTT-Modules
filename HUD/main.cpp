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
    
    //Texture
    Texture *tex0 = new Texture("resources/arma 1.png");
    Texture *tex1 = new Texture("resources/arma 2.png");
    Texture *tex2 = new Texture("resources/vida.png");
    Texture *tex4 = new Texture("resources/cooldown_arma 1.png");
    Texture *tex3 = new Texture("resources/cooldown_arma 2.png");
    Texture *tex5 = new Texture("resources/flash.png");
    Texture *tex6 = new Texture("resources/cooldown.png");
    Texture *tex7 = new Texture("resources/background.png");
    Texture *tex8 = new Texture("resources/hud.png");
    
    //Font
    Font *f = new Font("resources/font.ttf");
    
    //Guns ON
    
    Sprite *gun1 = new Sprite(tex0, 80, 80, 0, 0);
    gun1->move(17.0f,18.0f);
    Sprite *gun2 = new Sprite(tex1, 80, 80, 0, 0);
    gun2->move(17.0f,98.0f);
    /*Sprite *gun3 = new Sprite(tex3, 100, 100, 0, 0);
    gun3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *guns = new std::vector<Sprite*>();
    guns->push_back(gun1);
    guns->push_back(gun2);
    //guns->push_back(gun3);
    
    int activeGun = 0;
    
    //Guns Off
    Sprite *go1 = new Sprite(tex4, 80, 80, 0, 0);
    go1->move(17.0f,18.0f);
    Sprite *go2 = new Sprite(tex3, 80, 80, 0, 0);
    go2->move(17.0f,98.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsO = new std::vector<Sprite*>();
    gsO->push_back(go1);
    gsO->push_back(go2);
    //gsO->push_back(go3);
    
    //Guns Cooldown
    Sprite *gc1 = new Sprite(tex6, 80, 80, 0, 0);
    gc1->move(17.0f,18.0f);
    Sprite *gc2 = new Sprite(tex6, 80, 80, 0, 0);
    gc2->move(17.0f,98.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsC = new std::vector<Sprite*>();
    gsC->push_back(gc1);
    gsC->push_back(gc2);
    //gsO->push_back(go3);
    
    //Background
    Sprite *background = new Sprite(tex7, 1280, 720, 0, 0);
    
    //Background
    Sprite *background_hud = new Sprite(tex8, 1280, 720, 0, 0);
    
    //Player
    Sprite *plHP = new Sprite(tex2,100 , 15, 0, 0);
    plHP->move(200.0f,20.0f);
    
    int lifePlayer = 100;
    
    //Boss
    Sprite *bHP = new Sprite(tex2,100 , 15, 0, 0);
    bHP->move(590.0f,680.0f);
    
    int lifeBoss = 150;
    
    //Flash
    Sprite *fC = new Sprite(tex5,80 , 80, 0, 0);
    fC->move(100.0f,18.0f);
    
    //FlashOff
    Sprite *fCO = new Sprite(tex6,80 , 80, 0, 0);
    fCO->move(100.0f,18.0f);
    
    //HUD
    HUD *hud = new HUD(background, background_hud, plHP, bHP, f);
    hud->setSpriteFlash(fC);
    hud->setSpriteFlashCooldown(fCO);
    hud->setSpriteGunsCooldown(gsC);
    hud->setSpriteGunsOff(gsO);
    hud->setSpriteGunsOn(guns);
    
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

