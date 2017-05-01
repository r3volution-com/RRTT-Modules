#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Note.h"
#include "Boss.h"
#include "Enemy.h"
#include "NPC.h"
#include "Map.h"
#include "Gun.h"

class Level {
public:
    int level;
    
    Level(int numLevel);
    void drawAll();
    void enemyAI(Player *rath){enemy->AI(rath);}

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
    //Cargamos los enemigos
    void loadEnemy();
    //
    
    //Player se carga en levelState   
    Note *note;
    Boss *boss;
    Enemy *enemy;
    NPC *npc;
    Map *map;
    Gun *gun;
    
};

#endif /* LEVEL_H */

