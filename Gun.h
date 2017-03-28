#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Hitbox.h"
#include "Bullet.h"

class Gun {
    private:
        Animation *gunAnimation;
        Hitbox *hitbox;
        Bullet *attack;
        
        bool active;
        
        int damage;
        
        float attackCooldown;
        float attackMaxCooldown;
    public:
        Gun(Coordinate position, Rect<float> *animRect, Texture *tex);
        virtual ~Gun();
        
        void doAttack();
        
        void setPosition(Coordinate coord);
        void setAttack(Bullet *atk);
        void setActive();
        void setAttackCooldown(float atkCooldown) { attackCooldown = atkCooldown; }
        void setAttackMaxCooldown(float atkMCooldown) { attackMaxCooldown = atkMCooldown; }
        void setDamage(int dmg) { damage = dmg; }
        
        bool getActive() { return active; }
        int getDamage() { return damage; }
        float getAttackCooldown() { return attackCooldown; }
        float getAttackMaxCooldown() { return attackMaxCooldown; }
        Hitbox *getHitbox() { return hitbox; }
        Animation *getAnimation(){ return gunAnimation; }
};

#endif /* Gun_H */

