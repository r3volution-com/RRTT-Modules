#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "Gun.h"
#include "Entity.h"
#include "HUD.h"

class Player : public Entity {
    private:
        int hp;
        int maxHP;
        
        float maxFlashCooldown;
        float flashCooldown;
        int flashRange;
        
        Gun *weapon;
        std::vector<Gun*> *guns;
        int currentGun;
        
        bool weaponLoaded;
        
    public:
        Player(Rect<float> *playerData, float sp);
        virtual ~Player();
        
        void setWeapon(Gun *wP);
        bool changeGun(int gun);
        void weaponAttack(Rect<float> *Rect);
        void gunAttack(Rect<float> *Rect);
        
        void move(float x, float y);
        void flash(float dirX, float dirY);
        void respawn();
        void damage(int dmg);
        void die();
        
        void addGun(Gun *gun);
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        void setFlashRange(int range) { flashRange = range; }
        void setFlashCooldown(int cooldown);
        
        int getHP() { return hp; }
        int getMaxHP() { return maxHP; }
        Gun *getWeapon() { return weapon; }
        Gun *getCurrentGun() { return guns->at(currentGun); }
};

#endif /* PROTAGONISTA_H */

