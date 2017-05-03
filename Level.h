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
    
    Level(int numLevel);
    void drawAll();
    void enemyAI(Player *rath){enemy->AI(rath);}
    Enemy *enemy;
    Map *map;
    Crystals *getCrystal(){return crystal;}

private:

 /*-Protagonista prota
-Objeto things[ ]
-Jefe boss
-Enemigo enemy[ ]
-NPC npc
-Mapa map
-Arma gun[ ]
-Sprite sprite[ ]
-Ataque attack[ ]*/
    
    //Cargo el mapa
    void loadMap();
    //Cargamos las notas
    void loadNote();
    //Cargamos los cristales
    void loadCrystal();
    //Cargamos los enemigos
    void loadEnemy();
    //
    
    virtual ~Level();
    
    //Player se carga en levelState   
    Note *note;
    Boss *boss;
    NPC *npc;
    Gun *gun;
    Crystals *crystal;
    
};

#endif /* LEVEL_H */

