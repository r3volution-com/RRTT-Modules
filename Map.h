#ifndef MAP_H
#define MAP_H

#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class Map {
    private:
       
        XMLElement* map;
        XMLElement* img;       
        XMLElement *layer;
        XMLElement **data;
        XMLElement *capas;
        int ***_tilemap;
        
    public:
        XMLDocument doc;
        int _width, _height, _tileWidth, _tileHeight;
        const char *filename;
        int _numLayers;
        
        Map(const char* ruta); //ToDo: Sergio map
        
        //Almacenamos en cada posicion de data (cada posicion equivaldria a una capa) 
        //todas las etiquetas tile
        void dataTiles();
        
        //Obtenemos nueva coordenada X para el sprite del tile
        int NewCoordX(int gid);
        //Obtenemos nueva coordenada Y para el sprite del tile
        int NewCoordY(int gid);
        //Numero de capas que tiene el mapa
        void setNumLayers(int _numlayers);
};

#endif /* MAP_H */