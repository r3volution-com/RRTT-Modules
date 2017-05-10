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
    int level;
    Map *map;
    
    Level(int numLevel);
    void AI(Player *rath, HUD* hud);

    void Init();

    void Input();

    void Update(Player* rath, HUD* hud);

    void Render();
 
    Crystals *getCrystal(){return crystal;}
    std::vector<Enemy*> *getEnemys(){return enemys;}
    Boss *getBoss(){return boss;}

private:

    virtual ~Level();
    
    //Player se carga en levelState   
    Note *note;
    Boss *boss;
    NPC *npc;
    Gun *gun;
    Crystals *crystal;
    
    std::vector<Enemy*> *enemys;
};

#endif /* LEVEL_H */

