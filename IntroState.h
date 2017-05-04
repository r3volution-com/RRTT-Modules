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
        
        /**
         * Se realizan las primeras ejecuciones (se declara y ejecuta todo)
         */
        void Init();
        
        /**
         * Conjunto de teclas utilizadas
         */
        void Input();
         
        /**
         * Actualiza su contenido
         */
        void Update();
        
        /**
         * Encargado de imprimir por pantalla
         */
        void Render();
        
        /**
         * Encargado de limpiar
         */
        void CleanUp();
        
        virtual ~IntroState();

};

#endif /* INTROSTATE_H */

