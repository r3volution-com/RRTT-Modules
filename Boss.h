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
        /**
         * Crea un objeto de tipo jefe
         * @param position: Posicion del jefe. Tipo Coordinate
         * @param size: tamano del boss
         * @param sp: Velocidad de animacion del jefe
         */
        Boss(Coordinate position, Coordinate size, float sp); //ToDo: boss
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
        Gun *getCurrentGun() { return guns->at(currentGun); }
};

#endif /* BOSS_H */