#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameState.h"
#include "LevelState.h"
#include "MenuState.h"
#include "IntroState.h"


class Game {
    private:
        static Game* pinstance;
        LevelState *level;
        MenuState *menu;
        IntroState *intro;
        GameState *game;
        
    public:
        static Game* Instance();
        void Render();
        void Update();
        void Input();
        void ChangeCurrentState(const std::string &state);
        void getCurrentFPS();
        
        sf::RenderWindow *window;
        
        int fpsCounter;
        Time *fpsTimer;
        
        int iaSpeed;
        int fps;
        int iaps;
        
    protected:
        Game(); //: game(&intro) {}
        Game(const Game & );
        Game &operator = (const Game & );
};

#endif /* GAME_H */