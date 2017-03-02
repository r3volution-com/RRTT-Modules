#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "Entity.h"

class Player : public Entity {
    private:
        int hp;
        int maxHP;
        int flashRange;
        //Arma gun;
        
        void die();
    public:
        Player();
        virtual ~Player();
        
        //void changeGun(Arma g);
        void flash(int dirX, int dirY);
        void respawn();
        void gunAttack();
        void damage(int dmg);
        
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        void setFlashRange(int range) { flashRange = range; }
        
        int getHP() { return hp; }
        int getMaxHP() { return maxHP; }
        //Arma getArma() { return arma; }
};

#endif /* PROTAGONISTA_H */

