#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite.h"
#include "../HUD.h"
#include "../Coordinate.h"
#include "../Rect.h"
#include "../Player.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RRTT: Die Test");
    
    //Texture
    Texture *tex0 = new Texture("resources/sprites_hud.png");
    Texture *tex1 = new Texture("resources/background.png");
    Texture *tex2 = new Texture("resources/hud_die.png");
    Texture *tex3 = new Texture("resources/die.png");
    
    //Font
    Font *f = new Font("resources/font.ttf");
    
    //Guns ON
    
    int activeGun = 0;
    
    
    int lifePlayer = 100;
    
    //Boss
    int lifeBoss = 150;
    
    //Die
    Coordinate *coor = new Coordinate(600.0, 600.0);
    Rect<float> *rect = new Rect<float>(100, 100, 120, 30);
    
    //HUD
    HUD *hud = new HUD(tex1, tex2, tex0, f);
    hud->setButton(coor, tex0, rect);
    hud->setDieSprite(tex3);
    Rect<float> *rectPlayer = new Rect<float>(0,0,128,128);
    Texture *tex = new Texture("resources/sprites.png");
    Player *player = new Player(rectPlayer, 5.0);
    player->loadAnimation(tex, new Coordinate(0,0), 3, 0.1f);
    Button *button = hud->getButton();
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    Hitbox *mouse = new Hitbox(pos.x, pos.y, 1, 1);
    
    //Player
    
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
                player->damage(100-lifePlayer);
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            hud->resetClock();
        }
        
        pos = sf::Mouse::getPosition(*window);
        mouse->setPosition(pos.x, pos.y);
        button->hover(mouse);
        
        if(hud->checkDie() == true && button->getHover() == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            hud->resetStats();
            player->respawn();
            lifePlayer = 100;
        }
        
        window->clear();
        hud->drawHUD(window);
        hud->drawDie(window);
        window->draw(player->getAnimation()->getCurrentSprite());
        window->display();
        
    }
    return 0;
}

