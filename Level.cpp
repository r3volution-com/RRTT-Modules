#include "Level.h"

Level::Level(int numLevel) {
    
    //Guardamos el nivel a cargar
    level = numLevel;
    
    //Cargamos todos los elementos del juego
    loadMap();
    
}

void Level::loadMap(){
    
    //Cargamos bosque
    if(level==1){
        map = new Map("resources/bosque.tmx");
    }
    //Hacer coindiciones para el resto de mapas cuando esten creados
}

void Level::loadPlayer(){
    
}

void Level::drawAll(sf::RenderWindow *window){
    
    //Dibujamos todos los elementos
    map->dibujarMapa(window);
    
}
