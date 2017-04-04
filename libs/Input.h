#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <Thor/Input.hpp>

class Input {
    private:
        thor::ActionMap<std::string> map;
        thor::ActionMap<std::string>::CallbackSystem system;
    public:
        Input();
        virtual ~Input();
        
        void addAction(std::string name, thor::Action act);
        void addActionCallback(std::string name, thor::Action act, std::function< void()> nullaryListener);
        
        void update(sf::Window window);
        void callbacks(sf::Window window);
        
        bool isActive(std::string name);
};

#endif /* INPUT_H */