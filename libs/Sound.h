#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class Sound {
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
    public:
        Sound(std::string path);
        virtual ~Sound();
};

#endif /* SOUND_H */