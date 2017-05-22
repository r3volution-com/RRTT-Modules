#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Menu.h"
#include "libs/Time.h"
#include <SFML/Audio.hpp>

class MenuState : public GameState{
    private:
        Menu *principal;
        Menu *opciones;
        
        Menu *actual;
        
        
        Sprite *loading;
        Time *loadTime;
        
        int menuactual;
        bool loaded;
    public:
        MenuState();
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
        
        virtual ~MenuState();
};

#endif /* MENUSTATE_H */

