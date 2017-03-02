/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arma.h
 * Author: mario
 *
 * Created on 1 de marzo de 2017, 9:30
 */

#ifndef ARMA_H
#define ARMA_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Arma {
    private:
        bool active;
        
        float posX;
        float posY;
        
        float maxFlashCooldown;
        float flashCooldown;
        
        int damage;
        
        Texture texture;
        //Sprite sprite[];
        Rect<float> hitbox;
        
        //Ataque attack;
    public:
        Arma();
        virtual ~Arma();
        
        void loadSprite(Texture texture);
        void move(float dirX, float dirY);
        void attack();
        
        void setActive() {
            if (active) active = false;
            else active = true;
        }
        
        void setPosition(int x, int y){
            posX = x;
            posY = y;
        }
        
        void setFlashCooldown(int cooldown){
            maxFlashCooldown = cooldown;
            flashCooldown = cooldown;
        }
        
        void setDamage(int dmg) { damage = dmg; }
        
        bool getActive() { return active; }
        float getX() { return posX; }
        float getY() { return posY; }
        
        //float maxFlashCooldown;
        //float flashCooldown;
        //int damage;
        
        Rect<float> getHitbox() { return hitbox; }
        //Sprite getSprite(){ return sprite; }
        
};

#endif /* ARMA_H */

