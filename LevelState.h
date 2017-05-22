#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "libs/ResourceManager.h"
#include "libs/Trigonometry.h"
#include "libs/Particles.h"
#include "HUD.h"
#include "Player.h"
#include "Level.h"
#include "Console.h"
#include "Menu.h"

class LevelState : public GameState {
    private:
        Level *level;
        Player *rath;
        Trigonometry *tri;
        HUD *hud;
        Menu *pause;
        Sprite *damage;
        Sprite *victory;
        
        Time *end;
        bool finish;
        
        int currentLevel;
        
        float colX = 0.0f; //ToDo pabloF: esto aqui no y no se declaran valores en el .h
        float colY = 0.0f;
        
        bool paused;
        bool pauseMenu;
    public:
        
        LevelState();
        
        /**
         * Se realizan las primeras ejecuciones (se declara y ejecuta todo)
         */
        void Init();
        
        /**
         * Conjunto de teclas utilizadas
         */
        void Input();
        
        /**
         * Actualiza su contenido
         */
        void Update();
        
        /**
         * Encargado de imprimir por pantalla
         */
        void Render();
        
        /**
         * Encargado de limpiar
         */
        void CleanUp();
        
        void changeLevel();
        void changeLevelDirect(int numLvl);
        
        void setPaused(bool boolean){paused = boolean;}
        
        Level *getLevel(){return level;}
        Player *getRath(){return rath;}
        HUD *getHUD() {return hud;}
        bool getPaused(){return paused;}
        
        virtual ~LevelState();
        
};

#endif /* LEVELSTATE_H */
