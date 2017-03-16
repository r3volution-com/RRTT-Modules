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
    Texture *tex0 = new Texture("resources/homer.gif");
    Texture *tex1 = new Texture("resources/lenny.gif");
    Texture *tex4 = new Texture("resources/white.png");
    Texture *tex5 = new Texture("resources/rayo.jpg");
    Texture *tex6 = new Texture("resources/cooldown.png");
    Texture *tex7 = new Texture("resources/pyramid-background.jpg");
    

    //Guns ON
    
    Sprite *gun1 = new Sprite(tex0, 100, 100, 0, 0);
    Sprite *gun2 = new Sprite(tex1, 100, 100, 0, 0);
    gun2->move(0.0f,100.0f);
    /*Sprite *gun3 = new Sprite(tex3, 100, 100, 0, 0);
    gun3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *guns = new std::vector<Sprite*>();
    guns->push_back(gun1);
    guns->push_back(gun2);
    //guns->push_back(gun3);
    
    int activeGun = 0;
    
    //Guns Off
    Sprite *go1 = new Sprite(tex4, 100, 100, 0, 0);
    Sprite *go2 = new Sprite(tex4, 100, 100, 0, 0);
    go2->move(0.0f,100.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsO = new std::vector<Sprite*>();
    gsO->push_back(go1);
    gsO->push_back(go2);
    //gsO->push_back(go3);
    
    //Guns Cooldown
    Sprite *gc1 = new Sprite(tex6, 100, 100, 0, 0);
    Sprite *gc2 = new Sprite(tex6, 100, 100, 0, 0);
    gc2->move(0.0f,100.0f);
    /*Sprite *go3 = new Sprite(tex6, 100, 100, 0, 0);
    go3->move(0.0f,200.0f);*/
    
    std::vector<Sprite*> *gsC = new std::vector<Sprite*>();
    gsC->push_back(gc1);
    gsC->push_back(gc2);
    //gsO->push_back(go3);
    
    bool gunCooldown = false;
    bool gCd = false;
    
    //Background
    Sprite *background = new Sprite(tex7, 1920, 1024, 0, 0);
    
    //Player
    Sprite *plHP = new Sprite(tex4,100 , 15, 0, 0);
    plHP->move(150.0f,10.0f);
    
    int lifePlayer = 100;
    
    //Boss
    Sprite *bHP = new Sprite(tex4,100 , 20, 0, 0);
    bHP->move(590.0f,680.0f);
    
    int lifeBoss = 150;
    
    //Flash
    Sprite *fC = new Sprite(tex5,100 , 100, 0, 0);
    fC->move(100.0f,100.0f);
    
    bool flash = false;
    bool fCd = false;
    
    //FlashOff
    Sprite *fCO = new Sprite(tex6,100 , 100, 0, 0);
    fCO->move(100.0f,100.0f);
    
    //HUD
    HUD *hud = new HUD(background, guns, gsO, plHP, bHP, fC, fCO, gsC);
    
    
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
            if(fCd == false){
                flash = true;
                hud->resetClock();
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if(gCd == false){
                gunCooldown = true;
                hud->resetClock();
            }
        }
        
        
        hud->changeActiveGun(activeGun);        

        window->clear();
        hud->drawHUD(window);
        
       
        if(flash == true){
            fCd=hud->drawFlashCooldown(window);
            if(fCd == false){
                flash = false;
            }
        }
        if(gunCooldown == true){
            gCd=hud->drawGunCooldown(window);
            if(gCd == false){
                gunCooldown = false;
            }
        }
        
        window->display();
        
    }
    return 0;
}

