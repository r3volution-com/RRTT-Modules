#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState{
    
    public:
        //Pausar el juego
        virtual void Pause()=0;
        //Reanudar el juego
        virtual void Resume()=0;
        //Cuando cargue otro nivel, limpiar en el que estabamos (destructor)
        virtual void CleanUp()=0;
        virtual void Update()=0;
        virtual void Render(sf::Window window)=0;
        virtual void Input(sf::Window window)=0;
        
        //virtual ~GameState();
};

#endif

