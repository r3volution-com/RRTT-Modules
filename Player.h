#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "Gun.h"
#include "Entity.h"
#include "libs/Animation.h"
#include "libs/Time.h"

class Player : public Entity {
    private:
        Gun *weapon;
        std::vector<Gun*> *guns;
        
        int hp;
        int maxHP;
        
        Time *flashCooldown;
        int flashRange;
        
        bool weaponLoaded;
        
        int currentGun;
    public:
        Player(Coordinate position, Texture *t, Rect<float> newRect, float sp);
        virtual ~Player();
        
        void setWeapon(Gun *wP);
        bool changeGun(int gun);
        void weaponAttack();
        void gunAttack();
        
        void move(float xDir, float yDir);
        void flash(float dirX, float dirY);
        void respawn();
        void damage(int dmg);
        void die();
        
        void addGun(Gun *gun);
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        void setFlashRange(int range) { flashRange = range; }
        void setFlashCooldown(Time *cooldown);
        
        int getHP() { return hp; }
        int getMaxHP() { return maxHP; }
        Gun *getWeapon() { return weapon; }
        Gun *getCurrentGun() { return guns->at(currentGun); }
        Time *getFlashCooldown() { return flashCooldown;}
};

#endif /* PROTAGONISTA_H */

