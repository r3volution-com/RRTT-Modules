#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Hitbox.h"

class Gun {
    private:
        int width, height;
        bool active;
        
        int damage;
        
        Animation *gunAnimation;
        Hitbox *hitbox;
        
        float attackCooldown;
        float maxAttackCooldown;
        
        //Ataque attack;
    public:
        Gun(Coordinate *position, Rect *animRect, Texture *tex, int nS, float d);
        virtual ~Gun();
        
        void move(float dirX, float dirY);
        void attack();
        
        void setPosition(Coordinate *coord);
        void setRotation(float r);
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

