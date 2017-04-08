#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameState.h"
#include "LevelState.h"
#include "MenuState.h"
#include "IntroState.h"
#include "libs/Coordinate.h"
#include "libs/Time.h"


class Game {
    private:
        static Game* pinstance;
        LevelState *level;
        MenuState *menu;
        IntroState *intro;
        GameState *game;
        
        Time *fpsTimer;
    public:
        static Game* Instance();
        void Init();
        void Render();
        void Input();
        void Update();
        void ChangeCurrentState(const std::string &state);
        void getCurrentFPS();
        
        Coordinate *screenSize;
        sf::RenderWindow *window;
        
        int fpsCounter;
        
        int iaSpeed;
        int fps;
        int iaps;
        
    protected:
        Game(); //: game(&intro) {}
        Game(const Game & );
        Game &operator = (const Game & );
};

#endif /* GAME_H */