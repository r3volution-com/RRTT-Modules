#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include "Player.h"
#include "Note.h"
#include "Boss.h"
#include "Enemy.h"
#include "NPC.h"
#include "Map.h"
#include "Gun.h"
#include "Crystal.h"
#include "Obstacle.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class Level {
    private:
        //Json
        json j;

        //Variables
        int level;
        int enemigosCaidos;
        int actualRespawn;
        int npcMoving;
        int distanceToLock;
        bool seeBoss;
        bool showNPCText;
        bool showNoteText;
        bool paused;
        bool bossZone;
        bool activeIA;
        //Iniciar musica jefe
        bool play = false;
        bool isEnter = false;
        
        bool loaded = false;
        

        //Objetos
        HUD *hud;
        Player *rath;
        Map *map;
        Boss *boss;
        Trigonometry *tri;
        Text *keyIterationNpc;
        Sprite *loading;
        Time *loadTime;
        
        //Vectores
        std::vector<Coordinate*> respawn;
        std::vector<Enemy*> enemys;
        std::vector<Note*> notes;
        std::vector<NPC*> npcs;
        std::vector<Crystal*> crystals;
        std::vector<Obstacle*> preObstacles;
        std::vector<Obstacle*> postObstacles;
        std::vector<Hitbox*> endPoints;
    public:
        Level(Player* r, HUD* h);
        virtual ~Level();

        void Init(int numLevel);

        void Input();

        void Update();

        void RenderLevel();
        
        void RenderView();
        
        void CleanUp();
        
        /**
         * Actualiza el lanzamiento del nivel
         * @param booleano
         */
        void setIsEnter(bool booleano) {isEnter=booleano;}
        
        /**
         * Actualiza la zona del boss
         * @param b: Zona del boss
         */
        void setBossZone(bool b) { bossZone = b; }
        
        /**
         * Actualiza la pausa
         * @param p: Pausa;
         */
        void setPause(bool p){
            paused = p;
        }
        
        void setIA(bool ia){
            activeIA = ia; 
        }
        
        Coordinate* getRespawn(){ return respawn.at(actualRespawn);}

        Hitbox *colision(Hitbox *hitbox);

        std::vector<Enemy*> getEnemys(){return enemys;}
        Boss *getBoss(){return boss;}
        Map* getMap(){ return map; }
        Trigonometry *getTrignometry(){return tri;}
        bool getLoaded() {return loaded;}
        bool geIA(){return activeIA;}
        Sprite *getLoading() {return loading;}
};

#endif /* LEVEL_H */

