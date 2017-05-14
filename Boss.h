#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Gun.h"
#include "libs/Coordinate.h"


class Boss : public Enemy{
    private:
        std::vector<Gun*> *guns;
        
        Coordinate* dirFlash;
        
        int state;
        int actualState;
        std::vector<int> *states;
        
        Time *stateClock;
        Time *delay;
        
        bool onDelay;
        bool attacking;
        bool onRange;
        bool start;
        
        int level;
        float timeState;
        
        float initialSpeed;
        int currentGun;
        
        char dirSprite;
    public:
        /**
         * Crea un objeto de tipo jefe
         * @param position: Posicion del jefe. Tipo Coordinate
         * @param size: tamano del boss
         * @param sp: Velocidad de animacion del jefe
         */
        Boss(Coordinate position, Coordinate size, float sp, int lvl);
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
        void attackDone();
        void setPosition(Coordinate newCoor);
        void setPosition(float x, float y);
        void updatePosition(Coordinate newCoor);
        void updatePosition(float x, float y);
        
        Gun *getCurrentGun() { return guns->at(currentGun); }
        bool isAttacking() { return attacking; }
        bool getOnRange(){return onRange;}
        void setStateClock(Time *def){stateClock = def; timeState = stateClock->getTime(); stateClock = new Time(0);}
        void setAnimations(Texture *t, Rect<float> newRect);
        void move(float xDir, float yDir);
        void flash(float xDir, float yDir);
        void createStates();
        void changeState();
};

#endif /* BOSS_H */
