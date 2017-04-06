#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "HUD.h"

class LevelState:public GameState {
    private:
        HUD hud;
        
    public:
        LevelState(); //ToDo: level
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
        void populate(std::vector<sf::RectangleShape*> *objects, float x, float y);
};

#endif /* LEVELSTATE_H */