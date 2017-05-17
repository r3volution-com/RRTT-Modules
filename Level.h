#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Note.h"
#include "Boss.h"
#include "Enemy.h"
#include "NPC.h"
#include "Map.h"
#include "Gun.h"
#include "Crystals.h"

class Level {
public:

    Level(int numLevel);

    void Init();

    void Input(Player* rath, HUD* hud);

    void Update(Player* rath, HUD* hud);

    void Render();
 
    Crystals *getCrystal(){return crystal;}
    std::vector<Enemy*> *getEnemys(){return enemys;}
    Boss *getBoss(){return boss;}
    Coordinate* getRespawn(int num){ return respawn->at(num);}
    Map* getMap(){ return map; }
    Note* getNote() {return note;}
    NPC* getNPC() {return npc;}
    void setRespawn(int resp);
    void setMuestra(bool booleano) {muestra=booleano;};
    bool getMuestra() {return muestra;};
    bool getShowText() {return showText;}
    void setMoverse(bool booleano) {moverse=booleano;};
    bool getMoverse(){return moverse;}
    void setSinSalida(bool booleano) {sinSalida=booleano;};
    bool getSinSalida(){return sinSalida;}
    bool getShowIterationNpc(){return showIterationNpc;}
    void setPlay(bool booleano) {play=booleano;};
    Text *getKeyIterationNpc(){return keyIterationNpc;}
    Trigonometry *getTrignometry(){return tri;}
    int getDisNpcPlayer(){return disNpcPlayer;}
    void setDisNpcPlayer(int dis){disNpcPlayer = dis;}
    
private:

    virtual ~Level();
    
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
};

#endif /* LEVEL_H */

