#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "libs/ResourceManager.h"
#include "libs/Sprite.h"
#include "libs/Event.h"
#include "GameState.h"

class IntroState : public GameState{
    private:
        Sprite *background;
    public:
        IntroState();
        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();
        
        virtual ~IntroState();

};

#endif /* INTROSTATE_H */
