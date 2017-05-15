#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <Thor/Resources.hpp>
#include "Texture.h"
#include "Font.h"
#include "Sound.h"
#include "Music.h"

class ResourceManager {
    private:
	thor::ResourceHolder<Texture, std::string> textures;
	thor::ResourceHolder<Font,    std::string> fonts;
	thor::ResourceHolder<Sound, std::string>   sounds;
	thor::ResourceHolder<Music, std::string>   music;
        
    public:
        /**
         * Crea un Resource Manager
         */
        ResourceManager();
        virtual ~ResourceManager();
        
        /**
         * Carga de texturas
         * @param name: Nombre de las texturas
         * @param path: Ruta de las texturas
         */
        void loadTexture(std::string name, const char* path);
        
        /**
         * Carga de la fuente tipografica
         * @param name: Nombre de la fuente
         * @param path: Ruta de la fuente
         */
        void loadFont(std::string name, const char* path);
        
        /**
         * Carga de musica
         * @param name: Nombre de la musica
         * @param path: Ruta de la musica
         */
        void loadMusic(std::string name, const char* path);
        
        /**
         * Carga de sonidos
         * @param name: Nombre de la sonido
         * @param path: Ruta de la sonido
         */
        void loadSound(std::string name, const char* path);
        
        /**
         * Liberacion de las texturas
         * @param name:Nombre de las texturas
         */
        void releaseTexture(std::string name);
        
        /**
         * Liberacion de la fuente
         * @param: Nombre de la fuente
         * @return 
         */
        void releaseFont(std::string name);
        
        /**
         * Liberacion de la musica
         * @param: Nombre de la musica
         * @return 
         */
        void releaseMusic(std::string name);
        
        /**
         * Liberacion del sonido
         * @param: Nombre del sonido
         * @return 
         */
        void releaseSound(std::string name);
        
        Texture *getTexture(std::string name);
        Font *getFont(std::string name);
        Music *getMusic(std::string name);
        Sound *getSound(std::string name);
};

#endif /* RESOURCEMANAGER_H */