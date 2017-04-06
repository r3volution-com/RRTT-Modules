#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "LevelState.h"
#include "Menu.h"


class Game {
    private:
        static Game* pinstance;
        LevelState level;
        MenuState menu;
        IntroState intro;
        GameState *game;
        
    public:
        static Game* Instance();
        void Render();
        void Update();
        void Input();
        void ChangeCurrentState(const std::string &state);
        
        sf::RenderWindow *window;
        
    protected:
        Game() : game(&intro) {};
        Game(const Game & );
        Game &operator = (const Game & );
};

#endif /* GAME_H */