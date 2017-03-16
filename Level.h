#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <SFML/Graphics.hpp>

class Level {
    private:

    public:
        Level();
        void populate(std::vector<sf::RectangleShape*> *objects, float x, float y);
};

#endif /* LEVEL_H */