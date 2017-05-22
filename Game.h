#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameState.h"
#include "LevelState.h"
#include "MenuState.h"
#include "IntroState.h"
#include "Bullet.h"
#include "libs/Coordinate.h"
#include "libs/Time.h"


class Game {
    private:
        static Game* pinstance;
        LevelState *level;
        MenuState *menu;
        IntroState *intro;
        GameState *game;
        bool showFps;
        Text *fpsText;
        Time *fpsTimer;
        
    protected:
        Game(); //: game(&intro) {}
        virtual ~Game();
        Game(const Game & );
        Game &operator = (const Game & );
        
    public:
        static Game* Instance();
        
        Coordinate *screenSize;
        sf::RenderWindow *window;
        sf::View cameraView;
        
        
        ResourceManager *rM;
        Event *iM;
        Hitbox *mouse;
        Console *console;
        std::string temp;
        std::string currentScene;
        
        
        Time *iaTimer;
        int iaPS;
        int fps;
        int fpsCounter;
        
        float maxTime;
        float currentTime;
        float deltaTime;
        float interpolation;
        
        /**
         * Se realizan las primeras ejecuciones (se declara y ejecuta todo)
         */
        void Init();
        
        /**
         * Encargado de imprimir por pantalla
         */
        void Render();
        
        /**
         * Conjunto de teclas utilizadas
         */
        void Input();
        
        /**
         * Actualiza su contenido
         */
        void Update();
        
        /**
         * Cambia el estado actual
         * @param state: Estado al cual se debe de cambiar
         */
        void ChangeCurrentState(const std::string &state);
        LevelState *getLevelState(){return level;}
        std::string getCurrentScene(){
            return currentScene;
        }
        void setFps(bool f){
            showFps=f;
        }
        bool getFps(){
            return showFps;
        }
};

#endif /* GAME_H */