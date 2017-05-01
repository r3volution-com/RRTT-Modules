#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Gun.h"


class Boss : public Enemy{
    private:
        std::vector<Gun*> *guns;
        int state;
        int currentGun;
    public:
        Boss(Coordinate position, Texture *t, Rect<float> newRect, float sp); //ToDo: boss
        virtual ~Boss();
        void changeState(int s);
        void gunAttack();
        void addGun(Gun* gun);
        bool changeGun(int gun);
        //Gun *getCurrentGun() { return guns->at(currentGun); }
};

#endif /* BOSS_H */