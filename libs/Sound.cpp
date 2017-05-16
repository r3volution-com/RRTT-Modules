#include "Sound.h"
#include <iostream>

Sound::Sound(std::string path) {
    buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(path)){
        std::cerr << "Error cargando la musica " << path;
        exit(0);
    }
    sound = new sf::Sound();
    sound->setBuffer(*buffer);
}

Sound::~Sound() {
    delete buffer;
    delete sound;
    buffer = NULL;
    sound = NULL;
}