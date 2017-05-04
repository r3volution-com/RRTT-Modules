#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Menu.h"

class MenuState : public GameState{
    private:
        Menu *principal;
        Menu *opciones;
        
        Menu *actual;
        
        int menuactual;
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

