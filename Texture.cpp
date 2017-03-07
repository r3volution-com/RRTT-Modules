#include "Texture.h"

Texture::Texture(const char *path) {
    tex = new sf::Texture;
    if (!tex->loadFromFile(path)) {
        std::cerr << "Error cargando la imagen " << path;
        exit(0);
    }
}

Texture::Texture(sf::RenderTexture *t){
    tex=t; //ToDo: conversion de sf::RenderTexture a sf::Texture (o buscar alternativa)
}

Texture::~Texture() {
}

sf::RenderTexture *Texture::getRenderTexture(int w, int h) { 
    sf::RenderTexture *te;
    te->create(w, h);
    return te;
}