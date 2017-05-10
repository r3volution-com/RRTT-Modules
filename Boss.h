#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Gun.h"


class Boss : public Enemy{
    private:
        std::vector<Gun*> *guns;
        
        int state;
        
        Time *defensive;
        
        bool attacking;
        bool onRange;
        
        int level;
        
        int currentGun;
    public:
        /**
         * Crea un objeto de tipo jefe
         * @param position: Posicion del jefe. Tipo Coordinate
         * @param size: tamano del boss
         * @param sp: Velocidad de animacion del jefe
         */
        Boss(Coordinate position, Coordinate size, float sp, int lvl); //ToDo: boss
        virtual ~Boss();
        /**
         * Cambia el estado del jefe
         * @param s
         */
        void changeState(int s);
        
        /**
         * Ataque del arma
         */
        void gunAttack();
        
        /**
         * Anadir arma
         * @param gun: Puntero de arma
         */
        void addGun(Gun* gun);
        
        /**
         * Cambiar el arma
         * @param gun: Arma. Tipo int
         * @return 
         */
        bool changeGun(int gun);
        
        void AI(Player* rath, HUD* hud);
        
        Gun *getCurrentGun() { return guns->at(currentGun); }
        void attackDone();
        void setPosition(Coordinate newCoor);
        void setPosition(float x, float y);
        bool isAttacking() { return attacking; }
        bool getOnRange(){return onRange;}

};

#endif /* BOSS_H */