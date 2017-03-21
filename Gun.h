#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Hitbox.h"

class Gun {
    private:
        bool active;
        
        int damage;
        
        Animation *gunAnimation;
        Hitbox *hitbox;
        
        float attackCooldown;
        float maxAttackCooldown;
        
        //Ataque attack;
    public:
        Gun(float x, float y, int w, int h, Animation *gA);
        virtual ~Gun();
        
        void move(float dirX, float dirY);
        void attack();
        
        void setPosition(float x, float y);//ToDo: Sustituir todos los sitios donde se pasa x e y por coordenada
        void setActive();
        void setAttackCooldown(float atkCooldown);
        void setDamage(int dmg) { damage = dmg; }
        
        bool getActive() { return active; }
        int getDamage() { return damage; }
        float getAttackCooldown() { return attackCooldown; }
        
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return gunAnimation; }
        
};

#endif /* Gun_H */

