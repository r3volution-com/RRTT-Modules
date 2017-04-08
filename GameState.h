#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState{
    
    public:
        //Cuando cargue otro nivel, limpiar en el que estabamos (destructor)
        virtual void Init()=0;
        virtual void Input()=0;
        virtual void Update()=0;
        virtual void Render()=0;
        virtual void CleanUp()=0;
        
        //virtual ~GameState();
};

#endif

