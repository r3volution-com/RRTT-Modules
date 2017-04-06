#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <vector>
#include "GameState.h"
#include <SFML/Graphics.hpp>

#include "HUD.h"

class LevelState : public GameState {
    private:
        
    public:
        LevelState(); //ToDo: level
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
        void populate(std::vector<sf::RectangleShape*> *objects, float x, float y);
        
        virtual ~LevelState();
};

#endif /* LEVELSTATE_H */