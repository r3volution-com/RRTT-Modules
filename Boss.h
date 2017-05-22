#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Gun.h"
#include "libs/Coordinate.h"


class Boss : public Enemy{
    private:
        std::vector<Gun*> guns;
        
        Coordinate* dirFlash;
        
        int state;
        int actualState;
        std::vector<int> states;
        
        Time *stateClock;
        Time *delay;
        
        bool onDelay;
        bool attacking;
        bool onRange;
        bool start;
        bool nextState;
        
        float timeState;
        
        float initialSpeed;
        int currentGun;
        
        char dirSprite;
        
        int actualDmg;
        int angle;
        
    public:
        /**
         * Crea un objeto de tipo jefe
         * @param position: Posicion del jefe. Tipo Coordinate
         * @param size: tamano del boss
         * @param sp: Velocidad de animacion del jefe
         */
        Boss(Coordinate position, Coordinate size, float sp);
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
        
        Gun *getCurrentGun() { return guns.at(currentGun); }
        
        /**
         * Comprueba si esta atacando
         * @return attacking
         */
        bool isAttacking() { return attacking; }
        
        /**
         * Comprueba si está en el rango
         * @return 
         */
        bool getOnRange(){return onRange;}
        
        /**
         * Actualiza el reloj de estados 
         * @param def: De tipo tiempo
         */
        void setStateClock(float def){timeState = def;}
        
        /**
         * Actualiza las animaciones del boss
         * @param t: Sprite que utiliza
         * @param newRect: Zona que imprime
         */
        void setAnimations(Texture *t, Rect<float> newRect);
        
        /**
         * Movimiento del boss
         * @param xDir: Coordenada x. Tipo float
         * @param yDir: Coordenada y. Tipo float
         */
        void move(float xDir, float yDir);
        
        /**
         * Flash del boss
         * @param xDir
         * @param yDir
         */
        void flash(float xDir, float yDir);
        void changeState();
        
        /**
         * Dano que realiza el boss
         * @param dm: Cantidad de dano
         */
        void damage(int dm);
        
        /**
         * Anadir estado al boss
         * @param s: Numero del estado
         */
        void addState(int s);
        
        /**
         * Anadir estado aleatorio al boss
         * @param from: Estado actual
         * @param to: Estado al que tiene que cambiar
         */
        void addRandomState(int from, int to);
        int getStateBoss(){return state;}
        int getAngle(){return angle;}
};

#endif /* BOSS_H */
