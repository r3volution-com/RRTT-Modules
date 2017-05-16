#include "Music.h"
#include <iostream>

Music::Music(std::string path) {
    music = new sf::Music();
    if (!music->openFromFile(path)){
        std::cerr << "Error cargando la musica " << path;
        exit(0);
    }
}

Music::~Music() {
    delete music;
    music = NULL;
}