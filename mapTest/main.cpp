#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "../tinyxml2/tinyxml2.h"
#include "../Sprite.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]) {

    XMLDocument doc;
    doc.LoadFile( "resources/bosque.tmx" );
    
    cout << doc.ErrorID() << "\n";
    
    XMLElement* map = doc.FirstChildElement("map");
    
    int _width, _height, _tileWidth, _tileHeight; 

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    map->QueryIntAttribute("tilewidth", &_tileWidth);
    map->QueryIntAttribute("tileheight", &_tileHeight);
    
    cout << "Anchura: " << _width << "\n";
    cout << "ALtura: " << _height << "\n";
    cout << "TileWidth: " << _tileWidth << "\n";
    cout << "TIleHeight: " << _tileHeight << "\n";
    
    XMLElement* img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");
    
    cout << "Nombre de la imagen tileset: " << filename << "\n";
    
    XMLElement *layer = map->FirstChildElement("layer");
    int _numLayers=0;
    
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    cout << "Numero de capas: " << _numLayers << "\n";
    
    vector<XMLElement*> *data = new vector<XMLElement*>();
          
    for(int i=0; i<_numLayers;i++){
        data->push_back(map->FirstChildElement("layer")
        ->FirstChildElement("data")->FirstChildElement("tile"));
    }
   
    int ***_tilemap;
    
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
                data->at(l)->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                
                data->at(l) = data->at(l)->NextSiblingElement("tile");
                
            }
        }
    }
    
    
    //Creacion del array de sprites
    
    Sprite ****_tilemapSprite;
    
    _tilemapSprite = new Sprite***[_numLayers];
    
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l] = new Sprite**[_height];
        for(int y=0; y<_height; y++){
            _tilemapSprite[l][y] = new Sprite*[_width];
            for(int x=0; x<_width; x++){
                //Falta añadir new sprite
            }
        }
    }
    
    return 0;

}