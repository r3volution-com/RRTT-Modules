#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "libs/ResourceManager.h"
#include "GameState.h"
#include "Player.h"

class IntroState : public GameState{
    private:
        ResourceManager *rM;
        Texture *playerTexture;
        Player *rath;
    public:
        IntroState();
        void Render();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
        
        virtual ~IntroState();

};

#endif /* INTROSTATE_H */

