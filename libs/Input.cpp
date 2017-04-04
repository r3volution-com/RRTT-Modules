#include "Input.h"

Input::Input() {
}

Input::~Input() {
}

void Input::addAction(std::string name, thor::Action act){
    map[name] = act;
}

void Input::addActionCallback(std::string name, thor::Action act, std::function< void()> nullaryListener){
    map[name] = act;
    system.connect(name, nullaryListener);
}

void Input::update(sf::Window window){
    map.update(window);
    map.invokeCallbacks(system, &window);
}

bool Input::isActive(std::string name){
    return map.isActive(name);
}