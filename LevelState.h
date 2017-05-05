#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "libs/ResourceManager.h"
#include "libs/Trigonometry.h"
#include "HUD.h"
#include "Player.h"
#include "Level.h"
#include "Console.h"

class LevelState : public GameState {
    private:
        Level *level;
        Player *rath;
        Trigonometry *tri;
        HUD *hud;
        
        int direcX = 'r';
        int direcNow = 'z';
        bool mov = false;
        char colision = 'z';
        float mouseAng = 0.0f;
        float mousePos[2]={0,0};
        //float windowSize[2]={Game::Instance()->window->getSize().x/2, Game::Instance()->window->getSize().y/2};
        bool ata=false;
        
        sf::RectangleShape rectangle;
    public:
        LevelState();
        
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
        
        virtual ~LevelState();
};

#endif /* LEVELSTATE_H */
