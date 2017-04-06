#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState{
    
    public:
        //Se hace antes de inicializar el juego
        virtual void Init();
        //Pausar el juego
        virtual void Pause();
        //Reanudar el juego
        virtual void Resume();
        //Cuando cargue otro nivel, limpiar en el que estabamos (destructor)
        virtual void CleanUp();
        virtual void Update();
        virtual void Render();
        virtual void Input();
};

#endif

