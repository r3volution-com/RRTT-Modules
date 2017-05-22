#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"
#include "HUD.h"
#include "libs/Animation.h"
#include "libs/Time.h"
#include "libs/Trigonometry.h"
#include "libs/Particles.h"

class Enemy : public Entity{
    private:
        Trigonometry *tri;
        Particles *blood;
        int hp;
        int type;
        int maxHP;
        int flashRange;
        float maxFlashCooldown;
        float initialSpeed;
        float coolHit;
        
        Time *cd;
        Time *flashCooldown;
        Time *timeDead;
        
        bool home;
        bool freeze;
        bool haveParticles;
        bool dead;
        
        int slowDown;
        int dmgHit;
        int hits;
        int initialDmg;
        
        int disPlayerEnemy;
        int disEnemyHome;

        char direction;
        
        
    public: 
        /**
         * Se crea el objeto enemona a mostrar de la textura del enemigoigo
         * @param position: Se le otorga una posicion al enemigo de tipo coordenada
         * @param size: Tamano del enemigo
         * @param sp: Velocidad del enemigo
         */
        Enemy(Coordinate position, Coordinate size, float sp);
        virtual ~Enemy();
        
        /**
         * 
         * @param texture
         */
        void setBlood(Texture *texture);
        
        /**
         * 
         * @param duration
         */
        void startBlood(float duration);
        
        /**
         * 
         */
        void drawBlood();
        
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
        void setFlashCooldown(float cooldown);
        
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
        void setHitCooldown(float cool);
        
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
        void setFreeze(int num) {slowDown = num;}
        
        /**
         * Inteligencia artificil
         * @param rath: Puntero del personaje
         */
        void AI(Player *rath, HUD* hud);
        
        int getType(){return type;}
        int getDmg(){return dmgHit;}
        int getFlashRange(){return flashRange;}
        float getMaxFlashCooldown(){return maxFlashCooldown;}
        Trigonometry *getTrigonometry(){return tri;}
        Time *getCooldownHit(){return cd;}
        bool getHome(){return home;}
        bool getFreeze(){return freeze;}
        int getSlowDown(){return slowDown;}
        int getDisPlayerEnemy(){return disPlayerEnemy;}
        int getDisEnemyHome(){return disEnemyHome;}
        void setHome(bool value){home = value;}
        void resetCooldownHit(){cd->restart();}
        void setAnimations(Texture *t, Rect<float> newRect);
        float getInitialSpeed() {return initialSpeed;}
        int getInitialDmg() {return initialDmg;}
        void setInitialDmg(int dmg) {initialDmg = dmg; dmgHit = dmg; cd->start();} 
        void setHP(int ahp) {hp = ahp; }
        Time *getTimeDead() {return timeDead;}
        bool isDead(){return dead;}
        void setDead(bool d){ dead = d;}
};

#endif /* ENEMY_H */
