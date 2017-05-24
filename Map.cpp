#include "Map.h"
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Map::Map(const char* ruta, const char* texture) {
 
    doc.LoadFile(ruta);
    
    _tilesetTexture = new Texture(texture);

    map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    map->QueryIntAttribute("tilewidth", &_tileWidth);
    map->QueryIntAttribute("tileheight", &_tileHeight); 
    
    tileset = map->FirstChildElement("tileset");
    
    tileset->QueryIntAttribute("columns", &_columns);
    
    img = map->FirstChildElement("tileset")->FirstChildElement("image");
    filename = img->Attribute("source");

    layer = map->FirstChildElement("layer");
    objectgroup = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    _numLayers=0;
    
    muros = new std::vector<Hitbox*>();
    
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
    
    //Almacenamos los valores en la capa de objetos
    while(objectgroup){
        
        Hitbox *hitbox = new Hitbox(objectgroup->FloatAttribute("x"),objectgroup->FloatAttribute("y")
        ,objectgroup->IntAttribute("width"),objectgroup->IntAttribute("height")); 
        
        /*_objectX.push_back(objectgroup->FloatAttribute("x"));
        _objectY.push_back(objectgroup->FloatAttribute("y"));
        _objectW.push_back(objectgroup->FloatAttribute("width"));
        _objectH.push_back(objectgroup->FloatAttribute("height"));*/
        
        muros->push_back(hitbox);
        
        objectgroup = objectgroup->NextSiblingElement("object");
    }
    
    //Mostramos valores de la capa de objetos
    for(int i=0; i<_objectX.size(); i++){
        /*cout << "X: " << _objectX.at(i) << ", Y: " 
             << _objectY.at(i) << ", W: " << _objectW.at(i) 
             << " , H: " << _objectH.at(i) << endl;*/
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
    
    //Creamos el array de rects
    
    //Creamos el array de sprites
    matrizSprites();
    
}


Map::~Map(){
    

    doc.Clear();
    delete _tilesetTexture;
    

    map->DeleteChildren();
    tileset->DeleteChildren();
    img->DeleteChildren();
    layer->DeleteChildren();
    objectgroup->DeleteChildren();
    capas->DeleteChildren();
    _tilesetTexture = NULL;
    
    //Pruebas
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                //Vamos comparando
                delete _tilemapSprite[l][y][x];
                _tilemapSprite[l][y][x] = NULL;
            }
        }
    } 
    
    delete data;
    
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            //Vamos comparando
            data[y][x].DeleteChildren();
        }
     }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                //Vamos comparando
                //delete _tilemap[l][y][x];
                _tilemap[l][y][x] = 0;
            }
        }
    }
    
    for(int i=0; i < muros->size(); i++){
        delete muros->at(i);
        muros->at(i) = NULL;
    }
    
    muros->clear();
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                //Vamos comparando
                delete _tilemapSprite[l][y][x];
                _tilemapSprite[l][y][x] = NULL;
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

void Map::matrizSprites(){
    
    //j["map"].get<std::string>().c_str()
     
    Rect <float> *medidas = new Rect <float> (0, 0, 128, 128);
    
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

                    medidas->setRect(newX-_tileWidth, newY, 128, 128);
                    
                    
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
    
    int newX = (gid/_columns);
                    
    if(gid%_columns==0){
        newX = newX-1;
    }

    if(newX>0){
        newX = _tileWidth*(gid-(newX*_columns)); 
    }else{
        newX = (gid*_tileWidth);
    }
    
    return newX;
}

int Map::NewCoordY(int gid){
    
    int newY;
    
    newY = (gid/_columns)*_tileHeight;
                    
    if(gid%_columns==0){
        newY = newY-_tileHeight;
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

int Map::getGid(Enemy *enemy, int id1, int id2){
    
    //Obtenemos las coordenadas del enemigo
    Coordinate* coord = new Coordinate (enemy->getCoordinate()->x, enemy->getCoordinate()->y);
    
    //Acceder al gid del tile mediante las coord del enemigo
    // if _tilemapSprite[l][x][y] equals coord
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                //Vamos comparando
            }
        }
    }
    
    return 0;
    
}


