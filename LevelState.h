#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "libs/ResourceManager.h"
#include "libs/Trigonometry.h"
#include "HUD.h"
#include "Player.h"
#include "Level.h"
#include "Console.h"

class LevelState : public GameState {
    private:
        Level *level;
        ResourceManager *rM;
        Texture *playerTexture;
        Player *rath;
        int direcX = 'r';
        int direcNow = 'z';
        bool mov = false;
        char colision = 'z';
        float mouseAng = 0.0f;
        float mousePos[2]={0,0};
        //float windowSize[2]={Game::Instance()->window->getSize().x/2, Game::Instance()->window->getSize().y/2};
        bool ata=false;
        Trigonometry *tri;
        Enemy *enemy2;
        HUD *hud;
        Gun *gunArm;
    public:
        LevelState(); //ToDo: level
        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();
        
        virtual ~LevelState();
};

#endif /* LEVELSTATE_H */
