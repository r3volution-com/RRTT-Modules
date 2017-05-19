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
#include "libs/json.hpp"

using json = nlohmann::json;

class Level {
    private:
        json j;

        //Player se carga en levelState 
        int level;
        int enemigosCaidos;
        int actualRespawn;
        bool muestra = false;
        bool showText = false;
        //Comprobar si el npc se tiene que mover
        bool npcMove = false;
        //Que el muro se mantenga
        bool sinSalida = true;
        //Iniciar musica jefe
        bool play = false;

        bool showIterationNpc;

        HUD *hud;
        Player *rath;
        Map *map;
        Boss *boss;
        Trigonometry *tri;
        Text *keyIterationNpc;
        Entity *fuego;
        Entity *fuego2;

        std::vector<Coordinate*> *respawn;
        std::vector<Enemy*> *enemys;
        std::vector<Note*> *notes;
        std::vector<NPC*> *npcs;
        std::vector<Crystal*> *crystals;
    public:

        Level(Player* r, HUD* h);
        virtual ~Level();

        void Init(int numLevel);

        void Input();

        void Update();

        void Render();
        
        void CleanUp();
        
        void setRespawn(int resp);
        void setMuestra(bool booleano) {muestra=booleano;};
        void setNpcMove(bool booleano) {npcMove=booleano;};
        void setSinSalida(bool booleano) {sinSalida=booleano;};
        void setPlay(bool booleano) {play=booleano;};

        std::vector<Enemy*> *getEnemys(){return enemys;}
        /*Crystal *getCrystal(){return crystal;}
        Note* getNote() {return note;}
        NPC* getNPC() {return npc;}*/
        Boss *getBoss(){return boss;}
        Coordinate* getRespawn(){ return respawn->at(actualRespawn);}
        Map* getMap(){ return map; }
        Text *getKeyIterationNpc(){return keyIterationNpc;}
        Trigonometry *getTrignometry(){return tri;}
        bool getMuestra() {return muestra;}
        bool getShowText() {return showText;}
        bool getNpcMove(){return npcMove;}
        bool getSinSalida(){return sinSalida;}
        bool getShowIterationNpc(){return showIterationNpc;}
};

#endif /* LEVEL_H */

