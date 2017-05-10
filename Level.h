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

    void Input();

    void Update(Player* rath, HUD* hud);

    void Render();
 
    Crystals *getCrystal(){return crystal;}
    std::vector<Enemy*> *getEnemys(){return enemys;}
    Boss *getBoss(){return boss;}
    Coordinate* getRespawn(int num){ return respawn->at(num);}
    Map* getMap(){ return map; }
    void setRespawn(int resp);
    
private:

    virtual ~Level();
    
    //Player se carga en levelState 
    int level;
    Map *map;
    Note *note;
    Boss *boss;
    NPC *npc;
    Gun *gun;
    Crystals *crystal;
    std::vector<Coordinate*> *respawn;
    std::vector<Enemy*> *enemys;
};

#endif /* LEVEL_H */

