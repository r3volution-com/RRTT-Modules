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
        
        Time *fpsTimer;
    public:
        static Game* Instance();
        void Init();
        void Render();
        void Input();
        void Update();
        void ChangeCurrentState(const std::string &state);
        virtual ~Game();
        
        Coordinate *screenSize;
        sf::RenderWindow *window;
        sf::View cameraView;
        sf::View screenView;
        
        ResourceManager *rM;
        Event *iM;
        Hitbox *mouse;
        Console *console;
        std::string temp;
        
        Time *iaTimer;
        int iaPS;
        int fps;
        int fpsCounter;
        
        float maxTime;
        float currentTime;
        float deltaTime;
        float interpolation;
        
        
        std::vector<Bullet*> *bullets;
        
    protected:
        Game(); //: game(&intro) {}
        Game(const Game & );
        Game &operator = (const Game & );
};

#endif /* GAME_H */