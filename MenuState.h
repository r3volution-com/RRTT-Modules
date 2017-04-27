#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

class MenuState : public GameState{
    public:
        MenuState();
        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();
        
        virtual ~MenuState();
    
    private:

};

#endif /* MENUSTATE_H */

