#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"
#include "HUD.h"
#include "libs/Animation.h"
#include "libs/Time.h"
#include "libs/Trigonometry.h"

class Enemy : public Entity{
    private:
        int hp;
        int type;
        int maxHP;
        int dmg; //daño que hace
        int flashRange;
        Time *flashCooldown;
        float maxFlashCooldown;
        Trigonometry *tri;
        
        Time *cd;
        
        bool home;
        bool freeze;
        int dmgFreeze;
        int dmgHit;
        int hits;
        
        int disPlayerEnemy;
        int disEnemyHome;

        
    public: 
        /**
         * Se crea el objeto enemona a mostrar de la textura del enemigoigo
         * @param position: Se le otorga una posicion al enemigo de tipo coordenada
         * @param size: Tamano del enemigo
         * @param sp: Velocidad del enemigo
         */
        Enemy(Coordinate position, Coordinate size, float sp); //ToDo: enemy
        virtual ~Enemy();
        
        
        /**
         * Establece la vida maxima
         * @param mhp: valor entero de la vida
         */
        void setMaxHP(int mhp) { maxHP = mhp; hp = maxHP; }
        
        /**
         * El enemigo realiza un flash
         * @param dirX: Coordenada x en la que hacer el flash
         * @param dirY: Coordenada y en la que hacer el flash
         */
        void flash (float dirX, float dirY);
        
        /**
         * Actualiza el rango de alcace del flash
         * @param range: Rango de alcance del flash
         */
        void SetFlashRange(int range) { flashRange=range; }
        
        /**
         * Daño que realiza el enemigo
         * @param dm: Cantidad de daño realizada (tipo int)
         */
        void damage(int dm);
        
        /**
         * Movimiento del enemigo
         * @param xDir: Coordenada de direccion x
         * @param yDir: Coordenada de direccion y
         */
        void move(float xDir, float yDir);
        
        /**
         * Muerte del enemigo
         */
        void die();
        
        /**
         * Actualiza el tiempo de enfriamiento del flash del enemigo
         * @param cooldown: Tiempo de enfriamiento
         */
        void setFlashCooldown(Time *cooldown);
        
        int getHP() {return hp; }
        int getMaxHP() { return maxHP; }
        Time *getFlashCooldown() { return flashCooldown;}
        
        /**
         * Actualiza el tipo de enemigo
         * @param num: Numero del tipo de enemigo
         */
        void setType(int num) {type = num;}
        
        /**
         * Actualiza el dano por golpe
         * @param num: Cantidad del dano del enemigo
         */
        void setDmgHit(int num) {dmgHit = num; cd->start();}
        
        /**
         * Actualiza el enfriamiento del golpe
         * @param cool
         */
        void setHitCooldown(Time *cool) {cd = cool ; cd->start();}
        
        /**
         * Actualiza la distancia entre el jugador y el enemigo
         * @param dis: Distancia entre jugador y enemigo
         */
        void setDistancePlayerEnemy(int dis) { disPlayerEnemy = dis;}
        
        /**
         * Actualiza la distancia entre el enemigo y su punto de aparicion
         * @param dis: Distancia entre el enemgio y su punto de aparicion
         */
        void setDistanceEnemyHome(int dis) { disEnemyHome = dis;}
        
        /**
         * Relentizacion del enemigo, solo para los tipo 3
         * @param num: Relentizacion (tipo int)
         */
        void setFreeze(int num) {dmgFreeze = num;}
        
        /**
         * Inteligencia artificil
         * @param rath: Puntero del personaje
         */
        void AI(Player *rath, HUD* hud);
};

#endif /* ENEMY_H */
