#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite.h"
#include "../HUD.h"
#include "../Coordinate.h"
#include "../Rect.h"


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
    Texture *tex3 = new Texture("resources/cooldown_arma 2.png");
    Texture *tex4 = new Texture("resources/cooldown_arma 1.png");
    Texture *tex5 = new Texture("resources/flash.png");
    Texture *tex6 = new Texture("resources/cooldown.png");
    Texture *tex7 = new Texture("resources/background.png");
    Texture *tex8 = new Texture("resources/hud.png");
    Texture *tex9 = new Texture("resources/semi transparente pantalla.png");
    Texture *tex10 = new Texture("resources/boton die hud.png");
    
    //Font
    Font *f = new Font("resources/font.ttf");
    
    //Guns ON
    Rect *rectGun = new Rect(0, 0, 80, 80);
    Sprite *gun1 = new Sprite(tex0, rectGun);
    gun1->move(17.0f,18.0f);
    Sprite *gun2 = new Sprite(tex1, rectGun);
    gun2->move(17.0f,98.0f);
    /*Sprite *gun3 = new Sprite(tex3, 100, 100, 0, 0);
    gun3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *guns = new std::vector<Sprite*>();
    guns->push_back(gun1);
    guns->push_back(gun2);
    //guns->push_back(gun3);
    
    int activeGun = 0;
    
    //Guns Off
    Sprite *go1 = new Sprite(tex4, rectGun);
    go1->move(17.0f,18.0f);
    Sprite *go2 = new Sprite(tex3, rectGun);
    go2->move(17.0f,98.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsO = new std::vector<Sprite*>();
    gsO->push_back(go1);
    gsO->push_back(go2);
    //gsO->push_back(go3);
    
    //Guns Cooldown
    Sprite *gc1 = new Sprite(tex6, rectGun);
    gc1->move(17.0f,18.0f);
    Sprite *gc2 = new Sprite(tex6, rectGun);
    gc2->move(17.0f,98.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsC = new std::vector<Sprite*>();
    gsC->push_back(gc1);
    gsC->push_back(gc2);
    //gsO->push_back(go3);
    
    //Background
    Rect *rectBack = new Rect(0, 0, 1280, 720);
    Sprite *background = new Sprite(tex7, rectBack);
    
    //Background_HUD
    Sprite *background_hud = new Sprite(tex8, rectBack);
    
    //Player
    Rect *rectLife = new Rect(0, 0, 194, 14);
    Sprite *plHP = new Sprite(tex2, rectLife);
    plHP->move(200.0f,20.0f);
    
    int lifePlayer = 100;
    
    //Boss
    Sprite *bHP = new Sprite(tex2,rectLife);
    bHP->move(590.0f,680.0f);
    
    int lifeBoss = 150;
    
    //Flash
    Sprite *fC = new Sprite(tex5,rectGun);
    fC->move(100.0f,18.0f);
    
    //FlashOff
    Sprite *fCO = new Sprite(tex6, rectGun);
    fCO->move(100.0f,18.0f);
    
    //Die
    Sprite *sd = new Sprite(tex9, rectBack);
    
    Coordinate *coor = new Coordinate(600.0, 600.0);
    Rect *rect = new Rect(0, 0, 120, 30);
    
    //HUD
    HUD *hud = new HUD(background, background_hud, plHP, bHP, f);
    hud->setSpriteFlash(fC);
    hud->setSpriteFlashCooldown(fCO);
    hud->setSpriteGunsCooldown(gsC);
    hud->setSpriteGunsOff(gsO);
    hud->setSpriteGunsOn(guns);
    hud->setSpriteDie(sd);
    hud->setButton(coor, tex10, rect);
    
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
        hud->drawDie(window);
        
        window->display();
        
    }
    return 0;
}

