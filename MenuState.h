#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

class MenuState : public GameState{
    public:
        MenuState();
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
        
        virtual ~MenuState();
    
    private:

};

#endif /* MENUSTATE_H */

