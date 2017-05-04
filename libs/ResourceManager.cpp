#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    textures = thor::ResourceHolder<Texture,  std::string>();
    fonts    = thor::ResourceHolder<Font,     std::string>();
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

void ResourceManager::loadTexture(std::string name, const char* path) {
    textures.acquire(name, loadT(path));
}

void ResourceManager::loadFont(std::string name, const char* path) {
    fonts.acquire(name, loadF(path));
}

void ResourceManager::releaseTexture(std::string name){
    textures.release(name);
}

void ResourceManager::releaseFont(std::string name){
    fonts.release(name);
}

Texture *ResourceManager::getTexture(std::string name) {
    return &textures[name];
}
Font *ResourceManager::getFont(std::string name) {
    return &fonts[name];
}