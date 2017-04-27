
/* 
 * File:   main.cpp
 * Author: pablo
 *
 * Created on 15 de marzo de 2017, 9:43
 */

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdio>

#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    char direcX = 'r';
    char direcNow = 'z';
    float PI = 3.14159265f;
    float mouseAng = 0.0f;
    float mousePos[2]={0,0};
    float windowSize[2]={0,0};
    windowSize[0]=window.getSize().x/2;
    windowSize[1]=window.getSize().y/2;
    
    
    bool mov = true;
    bool ata = true;
    Texture *text = new Texture("resources/sprites.png");
    Player *rath = new Player(Coordinate(320, 240), text,Rect<float> (0, 0, 128, 128), 1.0f);
    //Gun *scytheArm = new Gun(new Coordinate(320, 240 ),new Rect<float>(0 ,512, 128 ,128), text, 1, 0.5f);
    Gun *gunArm = new Gun(Coordinate(300, 220), Rect<float> (0, 640, 128, 128), text);
    gunArm->getAnimation()->setOrigin(Coordinate(90,50));
    Enemy *enemy = new Enemy(Coordinate(500, 240), text, Rect<float> (0, 0, 128, 128), 1.0f);
    
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 4, 0.5f);
    rath->getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueAbajo", Coordinate(0, 1024), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueArriba", Coordinate(0, 1152), 2, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);
    
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    
    enemy->getAnimation()->addAnimation("enemyIdle", Coordinate(0, 0), 2, 0.25f);
    enemy->getAnimation()->initAnimator();
    enemy->getAnimation()->changeAnimation("enemyIdle", false);
    //rath->addAnimation('die', new Coordinate(X, X), 3, 0.5f);
    //rath->addAnimation('respawn', new Coordinate(X, X), 3, 0.5f);
    rath->addGun(gunArm);
    window.setFramerateLimit(120);
    //rath->setWeapon(scytheArm);
    
    
    //Bucle del juego
    while (window.isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                default: break;
            }
        }
        mousePos[0]=sf::Mouse::getPosition(window).x-windowSize[0];
        mousePos[1]=(sf::Mouse::getPosition(window).y-windowSize[1])*-1;
        if(mousePos[0]>=0 && mousePos[1]>=0){
            mouseAng=atan(mousePos[0]/mousePos[1])*180/PI+180;    
            //derecha arriba
        }
        else{if(mousePos[0]<=0 && mousePos[1]>=0){
            mousePos[0]=0-mousePos[0];
            mouseAng=atan(mousePos[1]/mousePos[0])*180/PI+90;
            //izquierda arriba
        }
        else{if(mousePos[0]<0 && mousePos[1]<0){
            mousePos[0]=0-mousePos[0];
            mousePos[1]=0-mousePos[1];
            mouseAng=atan(mousePos[0]/mousePos[1])*180/PI;
            //izquierda abajo
        }
        else{if(mousePos[0]>0 && mousePos[1]<0){
            mousePos[1]=0-mousePos[1];
            mouseAng=atan(mousePos[1]/mousePos[0])*180/PI+270;
            //derecha abajo
        }
        }
        }
        }
        gunArm->getAnimation()->setRotation(mouseAng);    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(mouseAng<315 && mouseAng>225){
                //derecha BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueDerecha", true);
                ata=true;
            }
            if(mouseAng<225 && mouseAng>135){
                //arriba BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueArriba", true);
                ata=true;
            }
            if(mouseAng<135 && mouseAng>45){
                //izquierda BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueIzquierda", true);
                ata=true;
            }
            if(mouseAng<45 || mouseAng>315){
                //abajo BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueAbajo", true);
                ata=true;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            if(direcNow!='u')
                rath->getAnimation()->changeAnimation("correrArriba", false);
            direcNow='u';
            mov=true;
        }

        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            //correr abajo
            rath->move(0, 1);
            if(direcX=='r' && direcNow!='d'){
                rath->getAnimation()->changeAnimation("correrDerecha", false);  
                mov=true;
                direcNow='d';
            }
            else{
                if(direcX=='l' && direcNow!='l'){
                    rath->getAnimation()->changeAnimation("correrIzquierda", false);
                    mov=true;
                    direcNow='d';
                }
            }
        }    
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            if(direcNow!='r')
                rath->getAnimation()->changeAnimation("correrDerecha", false);
            direcX='r';
            direcNow='r';
            mov=true;
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rath->move(-1, 0);
                if(direcNow!='l')
                rath->getAnimation()->changeAnimation("correrIzquierda", false);
                direcX='l';
                direcNow='l';
                mov=true;
            }
        }
        
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& mov==true){
            rath->getAnimation()->changeAnimation("idle", false);
            mov=false;
            direcNow='i';
        }
        if(ata==true){
            rath->getAnimation()->queueAnimation("idle", false);
            ata=false;
        }
        
        rath->getAnimation()->updateAnimator();
        gunArm->getAnimation()->updateAnimator();
        enemy->getAnimation()->updateAnimator();
        window.clear();
        window.draw(*gunArm->getAnimation()->getSprite());
        window.draw(*rath->getAnimation()->getSprite());
        window.draw(*enemy->getAnimation()->getSprite());
        window.display();   
    }
    return 0;
}
