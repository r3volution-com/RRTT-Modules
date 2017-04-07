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
    
}

void Map::dataTiles(){
            
    data = new XMLElement*[_numLayers];
    
    capas = map->FirstChildElement("layer");
    
    for(int i=0; i<_numLayers; i++){
        data[i] = capas->FirstChildElement("data")->FirstChildElement("tile");
        capas = capas->NextSiblingElement("layer");
    }
    
}

int Map::NewCoordX(int gid){
    
    
    
}

int Map::NewCoordY(int gid){
    
}

void Map::setNumLayers(int _numlayers){
    
}