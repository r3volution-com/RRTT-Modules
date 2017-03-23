#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy {
    private:
        int hp;
        int type;
        int maxHP;
        int damage; //daño que hace
        int flashRange;
        void die();
        
    public:
        Enemy(Rect *enemyData, float sp); //ToDo: enemy
        virtual ~Enemy();
        
        void move(float x, float y);
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        void flash (float dirX, float dirY);
        void SetFlashRange(int range) { flashRange=range; }
        
        void getHP() {return hp; }
        void getMaxHP() { return maxHP; }
        
};

#endif /* ENEMY_H */