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
        
        int getHP() {return hp; }
        int getMaxHP() { return maxHP; }
        
};

#endif /* ENEMY_H */
