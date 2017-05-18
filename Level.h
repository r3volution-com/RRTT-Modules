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
#include "Crystals.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class Level {
    private:
        json j;

        //Player se carga en levelState 
        int level;
        int enemigosCaidos;
        int disNpcPlayer;
        bool muestra = false;
        bool showText = false;
        //Comprobar si el npc se tiene que mover
        bool moverse = false;
        //Que el muro se mantenga
        bool sinSalida = true;
        //Iniciar musica jefe
        bool play = false;

        bool showIterationNpc;


        Text *keyIterationNpc;
        Map *map;
        Note *note;
        Boss *boss;
        NPC *npc;
        Entity *fuego;
        Entity *fuego2;
        Trigonometry *tri;

        Gun *gun;
        Crystals *crystal;
        std::vector<Coordinate*> *respawn;
        std::vector<Enemy*> *enemys;
    public:

        Level(int numLevel);
        virtual ~Level();

        void Init();

        void Input(Player* rath, HUD* hud);

        void Update(Player* rath, HUD* hud);

        void Render();
        
        void setRespawn(int resp);
        void setMuestra(bool booleano) {muestra=booleano;};
        void setMoverse(bool booleano) {moverse=booleano;};
        void setSinSalida(bool booleano) {sinSalida=booleano;};
        void setDisNpcPlayer(int dis){disNpcPlayer = dis;}
        void setPlay(bool booleano) {play=booleano;};

        std::vector<Enemy*> *getEnemys(){return enemys;}
        Crystals *getCrystal(){return crystal;}
        Boss *getBoss(){return boss;}
        Coordinate* getRespawn(int num){ return respawn->at(num);}
        Map* getMap(){ return map; }
        Note* getNote() {return note;}
        NPC* getNPC() {return npc;}
        Text *getKeyIterationNpc(){return keyIterationNpc;}
        Trigonometry *getTrignometry(){return tri;}
        int getDisNpcPlayer(){return disNpcPlayer;}
        bool getMuestra() {return muestra;};
        bool getShowText() {return showText;}
        bool getMoverse(){return moverse;}
        bool getSinSalida(){return sinSalida;}
        bool getShowIterationNpc(){return showIterationNpc;}
};

#endif /* LEVEL_H */

