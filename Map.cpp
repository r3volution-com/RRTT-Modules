#include "Map.h"
#include <iostream>

using namespace std;

Map::Map(const char* ruta) {
 
    doc.LoadFile(ruta);

    map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    map->QueryIntAttribute("tilewidth", &_tileWidth);
    map->QueryIntAttribute("tileheight", &_tileHeight); 
    
    img = map->FirstChildElement("tileset")->FirstChildElement("image");
    filename = img->Attribute("source");

    layer = map->FirstChildElement("layer");
    _numLayers=0;
    
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
    
    //Almacenamos las etiquetas tiles
    dataTiles();
    
    //Creamos el mapa de tiles
    _tilemap = new int**[_numLayers];
    
    
    //Reservamos memoria para el tilemap
    for(int i=0; i<_numLayers;i++){
        _tilemap[i] = new int*[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height;y++){
            _tilemap[l][y] = new int[_width];
        }
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                
                data[l] = data[l]->NextSiblingElement("tile");
                
            }
        }
    }
    
    //Creamos el array de sprites
    matrizSprites();
    
}

void Map::dataTiles(){
            
    data = new XMLElement*[_numLayers];
    
    capas = map->FirstChildElement("layer");
    
    for(int i=0; i<_numLayers; i++){
        data[i] = capas->FirstChildElement("data")->FirstChildElement("tile");
        capas = capas->NextSiblingElement("layer");
    }
    
}

void Map::matrizSprites(){
    
    Texture *_tilesetTexture = new Texture("resources/tileset3.png");
    
    Rect <float> *medidas = new Rect <float> (448, 96, 32, 32);
    
    _tilemapSprite = new Sprite***[_numLayers];
    
    //Rellenando el array de sprites
    
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l] = new Sprite**[_height];
        for(int y=0; y<_height; y++){
            _tilemapSprite[l][y] = new Sprite*[_width];
            for(int x=0; x<_width; x++){
                int gid = _tilemap[l][y][x];               
                    
                if(gid>0){
                    Coordinate* coord = new Coordinate (x*_tileWidth, y*_tileHeight);
                    
                    int newX, newY;                    
                    
                    //Obtenemos nueva coordenada x e y del rect medidas
                    newX = NewCoordX(gid);
                    newY = NewCoordY(gid);

                    medidas->setRect(newX-32, newY, 32, 32);
                    //Si fuera 0 no creo sprite...
                    
                    //Obtener getTextureRect de un vector/matriz de sprites donde cada sprite este asociado con su identificador de gid
                    //Es decir el gid/sprite 79 estara en las cordenadas 64, 64, 64, 64 (por ejemplo)
                    //Entonces a la hora de crear el mapa dependiendo del gid le pasariamos un rect float u otro, no siempre el mismo (como estoy haciendo ahora)
                    _tilemapSprite[l][y][x] = new Sprite(_tilesetTexture, 
                            *medidas);
                    
                    _tilemapSprite[l][y][x]->setPosition(*coord);
                    
                }else{             
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
}

int Map::NewCoordX(int gid){
    
    int newX = (gid/16);
                    
    if(gid%16==0){
        newX = newX-1;
    }

    if(newX>0){
        newX = 32*(gid-(newX*16)); 
    }else{
        newX= 0;
    }
    
    return newX;
}

int Map::NewCoordY(int gid){
    
    int newY = (gid/16)*32;
                    
    if(gid%16==0){
        newY = newY-1;
    }
    
    return newY;
}

void Map::setActiveLayer(int layer){
    
    todo = false;
    
    if(_numLayers>layer){
        _activeLayer = layer;
    }else{
        _activeLayer = 0;
    }
}

void Map::dibujarMapa(sf::RenderWindow *window){
     
    if(todo==false){
        //Se muestra solo la capa seleccionada
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                if(_tilemapSprite[_activeLayer][y][x]!=NULL){
                    //Dibujamos todas las capas
                    //Haciendo un metodo activeLayer podriamos elegir una sola capa
                    window->draw(*_tilemapSprite[_activeLayer][y][x]->getSprite());
                }
            }
        }
    }else{
        //Se muestra todo el mapa
        for(int l=0; l<_numLayers; l++){
            for(int y=0; y<_height; y++){
                for(int x=0; x<_width; x++){
                    if(_tilemapSprite[l][y][x]!=NULL){
                        //Dibujamos todas las capas
                        //Haciendo un metodo activeLayer podriamos elegir una sola capa
                        window->draw(*_tilemapSprite[l][y][x]->getSprite());
                    }
                }
            }
        }
    }
}