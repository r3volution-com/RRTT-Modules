#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <Thor/Resources.hpp>
#include "Texture.h"
#include "Font.h"

class ResourceManager {
    private:
	thor::ResourceHolder<Texture, std::string> textures;
	thor::ResourceHolder<Font,    std::string> fonts;
	//thor::ResourceHolder<sf::SoundBuffer, std::string>   sounds;
        
    public:
        ResourceManager();
        virtual ~ResourceManager();
        
        void loadTexture(std::string name, const char* path);
        void loadFont(std::string name, const char* path);
        
        void releaseTexture(std::string name);
        void releaseFont(std::string name);
        
        Texture *getTexture(std::string name);
        Font *getFont(std::string name);
};

#endif /* RESOURCEMANAGER_H */