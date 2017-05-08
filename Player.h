#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "Weapon.h"
#include "Gun.h"
#include "Entity.h"
#include "libs/Animation.h"
#include "libs/Time.h"

class Player : public Entity {
    private:
        Weapon *weapon;
        std::vector<Gun*> *guns;
        
        int hp;
        int maxHP;
        
        Time *flashCooldown;
        int flashRange;
        
        bool attacking;
        bool weaponLoaded;
        
        int currentGun;
        
        char state;
    public:
        /**
         * Crea el objeto jugador
         * @param position: Posicion del jugador (tipo coord)
         * @param size: Tamano del jugador (tipo coord)
         * @param sp: Velocidad de la animacion del jugador
         */
        Player(Coordinate position, Coordinate size, float sp);
        virtual ~Player();
        
        /**
         * Añade animaciones al jugador
         * @param t: Textura del jugador 
         * @param newRect: Zona del spritesheet donde esta el jugador
         */
        void setAnimations(Texture *t, Rect<float> newRect);
        
        /**
         * Actualiza el arma del jugador
         * @param wP: Arma del jugador (tipo gun)
         */
        void setWeapon(Weapon *wP);
        
        /**
         * Anadir arma
         * @param gun: Arma a anadir
         */
        void addGun(Gun *gun);
        
        /**
         * Cambia de arma 
         * @param gun: Arma (tipo int)
         * @return 
         */
        bool changeGun(int gun);
        
        /**
         * Ataque con el arma
         */
        void weaponChargeAttack();
        
        /**
         * Ataque con la pistola
         */
        void gunAttack();
        
        /**
         * Movimiento del jugador
         * @param xDir: Movimiento en la coordenada x
         * @param yDir: Movimiento en la coordenada y
         */
        void move(float xDir, float yDir);
        
        /**
         * Flash del jugador
         * @param dirX: Flash en la coordenada x
         * @param dirY: Flash en la coordenada y
         */
        void flash(float dirX, float dirY);
        
        /**
         * Reaparicion del jugador
         */
        void respawn(Coordinate coor);
        
        /**
         * Dano recibido por el jugador
         * @param dmg: Dano recibido
         */
        void damage(int dmg);
        
        /**
         * Muerte del jugador
         */
        void die();
        
        /**
         * Actualizar vida maxima del jugador
         * @param mhp: Vida maxima
         */
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        
        /**
         * Actualizar rango del flash del jugador
         * @param range: Rango del flash
         */
        void setFlashRange(int range) { flashRange = range; }
        
        /**
         * Actualizar el tiempo de enfriamiento del flash
         * @param cooldown: Tiempo de enfriamiento
         */
        void setFlashCooldown(Time *cooldown);
        
        /**
         * Actualiza la posicion del jugador
         * @param newCoor: Coodenada. Tipo Coordinate
         */
        void setPosition(Coordinate newCoor);
        
        /**
         * Actualiza la posicion del jugador
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setPosition(float x, float y);
        
        /**
         * Finaliza el ataque
         */
        void attackDone();
        
        int getHP() { return hp; }
        int getMaxHP() { return maxHP; }
        Weapon *getWeapon() { return weapon; }
        Gun *getCurrentGun() { return guns->at(currentGun); }
        Time *getFlashCooldown() { return flashCooldown; }
        
        bool isAttacking() { return attacking; }
};

#endif /* PROTAGONISTA_H */

