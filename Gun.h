#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Hitbox.h"
#include "Bullet.h"

class Gun {
    private:
        int width, height;
        bool active;
        
        int damage;
        
        Animation *gunAnimation;
        Hitbox *hitbox;
        
        float attackCooldown;
        float maxAttackCooldown;
        
        Bullet attack;
    public:
        Gun(Coordinate *position, Rect<float> *animRect, Texture *tex, int nS, float d);
        virtual ~Gun();
        
        void move(float dirX, float dirY);
        void doAttack(Rect<float> *Rect);
        
        void setPosition(Coordinate *coord);
        void setAttack(Bullet atk);
        void setRotation(float r);
        void setOrigin(float x, float y);
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

