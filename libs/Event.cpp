#include "Event.h"
#include "../Game.h"

Event::Event() {
}

Event::~Event() {
}

void Event::addAction(std::string name, thor::Action act){
    map[name] = act;
}

void Event::addActionCallback(std::string name, thor::Action act, std::function< void()> nullaryListener){
    map[name] = act;
    system.connect0(name, nullaryListener);
}

void Event::update(){
    map.update(*Game::Instance()->window);
    map.invokeCallbacks(system, Game::Instance()->window);
}

bool Event::isActive(std::string name){
    return map.isActive(name);
}