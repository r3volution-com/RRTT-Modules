#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"
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

        
    public: 
        /**
         * Se crea el objeto enemigo
         * @param position: Se le otorga una posicion al enemigo de tipo coordenada
         * @param t: Puntero con referencia a la textura del enemigo
         * @param newRect: Zona a mostrar de la textura del enemigo
         * @param sp: Velocidad del enemigo
         */
        Enemy(Coordinate position, Texture *t, Rect<float> newRect, float sp); //ToDo: enemy
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
        
        void move(float xDir, float yDir);
        
        void die();
        
        void setFlashCooldown(Time *cooldown);
        
        int getHP() {return hp; }
        int getMaxHP() { return maxHP; }
        Time *getFlashCooldown() { return flashCooldown;}
        void setType(int num) {type = num;}
        void setDmgHit(int num) {dmgHit = num; cd->start();}
        /**
         * Relentizacion del enemigo, solo para los tipo 3
         * @param num: Relentizacion (tipo int)
         */
        void setFreeze(int num) {dmgFreeze = num;}
        void AI(Player *rath);
};

#endif /* ENEMY_H */
