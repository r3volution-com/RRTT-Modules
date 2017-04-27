#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "libs/ResourceManager.h"
#include "HUD.h"
#include "Player.h"

class LevelState : public GameState {
    private:
        ResourceManager *rM;
        Texture *playerTexture;
        Player *rath;
        int direcX = 'r';
        int direcNow = 'z';
        bool mov = false;
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