#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Menu.h"

class MenuState : public GameState{
    private:
        Menu *principal;
        
    public:
        MenuState();
        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();
        
        virtual ~MenuState();
};

#endif /* MENUSTATE_H */

