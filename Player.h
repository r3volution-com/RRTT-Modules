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
        std::vector<Gun*> guns;
        
        int hp;
        int maxHP;
        
        Time *flashCooldown;
        float flashTime;
        int flashRange;
        
        float initialSpeed;
        
        bool attacking;
        bool weaponLoaded;
        
        int currentGun;
        
        char state;
        
        bool dead;
        Time *dmgOnPlayer;
        
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
        void weaponShortAttack(int angle);
        
        /**
         * Ataque con el arma
         */
        void weaponChargeAttack(int initialAngle);
        
        /**
         * Ataque con el arma
         */
        void weaponReleaseAttack();
        
        /**
         * Ataque con la pistola
         */
        void gunAttack();
        
        /**
         * Finaliza el ataque
         */
        void attackDone();
        
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
        void flash();
        
        /**
         * Reaparicion del jugador
         */
        void respawn();
        
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
        void setFlashCooldown(float cd);
        
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
         * Actualiza la posicion del jugador
         * @param newCoor: Coodenada. Tipo Coordinate
         */
        void updatePosition(Coordinate newCoor);
        
        /**
         * Actualiza la posicion del jugador
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void updatePosition(float x, float y);
        
        /**
         *llama a derecha() de gun
         */
        void derechaGun();
        
        /**
         *llama a inversa() de gun
         */
        void inversaGun();
        
        void setSpeed(float sp);
        
        int isDead() { return dead; }
        
        int getHP() { return hp; }
        int getMaxHP() { return maxHP; }
        int getCurrentGunId() { return currentGun; }
        Weapon *getWeapon() { return weapon; }
        Gun *getCurrentGun() { return guns.at(currentGun); }
        Time *getFlashCooldown() { return flashCooldown; }
        int getGunsNumber(){ return guns.size(); }
        
        bool isAttacking() { return attacking; }
        
        float getInitialSpeed() {return initialSpeed;}
        Time *getDmgOnPlayer() {return dmgOnPlayer;}
        std::vector<Gun*> getGuns() {return guns;}
        void restoreHP() {hp = maxHP;}
};

#endif /* PROTAGONISTA_H */

