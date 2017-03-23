#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity{
    private:
        int hp;
        int type;
        int maxHP;
        int dmg; //daño que hace
        int flashRange;
        void die();
        
    public:
        Enemy(Rect<float> *enemyData, float sp); //ToDo: enemy
        virtual ~Enemy();
        
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        void flash (float dirX, float dirY);
        void SetFlashRange(int range) { flashRange=range; }
        void damage(int dm);
        
        int getHP() {return hp; }
        int getMaxHP() { return maxHP; }
        
};

#endif /* ENEMY_H */