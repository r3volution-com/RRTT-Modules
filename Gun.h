#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Gun {
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
        Gun();
        virtual ~Gun();
        
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

#endif /* Gun_H */

