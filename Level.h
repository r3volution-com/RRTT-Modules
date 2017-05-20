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
        //Iniciar musica jefe
        bool play = false;
        

        //Objetos
        HUD *hud;
        Player *rath;
        Map *map;
        Boss *boss;
        Trigonometry *tri;
        Text *keyIterationNpc;
        //Vectores
        std::vector<Coordinate*> *respawn;
        std::vector<Enemy*> *enemys;
        std::vector<Note*> *notes;
        std::vector<NPC*> *npcs;
        std::vector<Crystal*> *crystals;
        std::vector<Obstacle*> *preObstacles;
        std::vector<Obstacle*> *postObstacles;
        
        sf::RectangleShape *shape;
    public:
        Level(Player* r, HUD* h);
        virtual ~Level();

        void Init(int numLevel);

        void Input();

        void Update();

        void Render();
        
        void CleanUp();
        
        void setPlay(bool booleano) {play=booleano;}
        void setBossZone(bool b) { bossZone = b; }
        
        Coordinate* getRespawn(){ return respawn->at(actualRespawn);}

        Hitbox *colision(Hitbox *hitbox);

        std::vector<Enemy*> *getEnemys(){return enemys;}
        Boss *getBoss(){return boss;}
        Map* getMap(){ return map; }
        Trigonometry *getTrignometry(){return tri;}
};

#endif /* LEVEL_H */

