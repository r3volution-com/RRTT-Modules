#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "GameState.h"

class IntroState : public GameState{
    public:
        IntroState();
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
        
        virtual ~IntroState();

    private:

};

#endif /* INTROSTATE_H */

