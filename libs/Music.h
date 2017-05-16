#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>

class Music {
    private:
        sf::Music *music;
    public:
        Music(std::string path);
        virtual ~Music();
        
        sf::Music *getMusic() { return music; }
};

#endif /* MUSIC_H */