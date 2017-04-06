#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "LevelState.h"
#include "Menu.h"


class Game {
    private:
        static Game* pinstance;
        Level *level;
        Menu *menu;
        
    public:
        static Game* Instance();
        void Render();
        void Update();
        void Init();
        void Input();
        
        sf::RenderWindow *window;
        
    protected:
        Game();
        Game(const Game & );
        Game &operator = (const Game & );
};

#endif /* GAME_H */