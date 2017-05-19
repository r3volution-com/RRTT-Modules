#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    textures = thor::ResourceHolder<Texture,  std::string>();
    fonts    = thor::ResourceHolder<Font,     std::string>();
    sounds    = thor::ResourceHolder<Sound,    std::string>();
    music    = thor::ResourceHolder<Music,    std::string>();
}

ResourceManager::~ResourceManager() {
    /*delete textures;
    delete fonts;
    textures = NULL;
    fonts = NULL;*/
}
        
thor::ResourceLoader<Texture> loadT(const char* filename) {
    return thor::ResourceLoader<Texture>([=] () { 
        return std::unique_ptr<Texture>(new Texture(filename));
    }, filename);
}

thor::ResourceLoader<Font> loadF(const char* filename) {
    return thor::ResourceLoader<Font>([=] () { 
        return std::unique_ptr<Font>(new Font(filename)); 
    },filename);
}

thor::ResourceLoader<Music> loadM(const char* filename) {
    return thor::ResourceLoader<Music>([=] () { 
        return std::unique_ptr<Music>(new Music(filename)); 
    },filename);
}

thor::ResourceLoader<Sound> loadS(const char* filename) {
    return thor::ResourceLoader<Sound>([=] () { 
        return std::unique_ptr<Sound>(new Sound(filename)); 
    },filename);
}

void ResourceManager::loadTexture(std::string name, const char* path) {
    textures.acquire(name, loadT(path));
}

void ResourceManager::loadFont(std::string name, const char* path) {
    fonts.acquire(name, loadF(path));
}

void ResourceManager::loadMusic(std::string name, const char* path) {
    music.acquire(name, loadM(path));
}

void ResourceManager::loadSound(std::string name, const char* path) {
    sounds.acquire(name, loadS(path));
}

void ResourceManager::releaseTexture(std::string name){
    textures.release(name);
}

void ResourceManager::releaseFont(std::string name){
    fonts.release(name);
}

void ResourceManager::releaseMusic(std::string name){
    music.release(name);
}

void ResourceManager::releaseSound(std::string name){
    sounds.release(name);
}

Texture *ResourceManager::getTexture(std::string name) {
    return &textures[name];
}

Font *ResourceManager::getFont(std::string name) {
    return &fonts[name];
}

Sound *ResourceManager::getSound(std::string name) {
    return &sounds[name];
}

Music *ResourceManager::getMusic(std::string name) {
    return &music[name];
}