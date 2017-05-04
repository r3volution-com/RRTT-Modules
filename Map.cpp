#include "Map.h"
#include "Game.h"
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
    
    //Creamos el array de rects
    
    //Creamos el array de sprites
    matrizSprites();
    
}


Map::~Map(){

    delete _tilemapSprite;
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                //Vamos comparando
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
    
    Texture *_tilesetTexture = new Texture("resources/oj2.png");
    
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

                    medidas->setRect(newX-128, newY, 128, 128);
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
    
    int newX = (gid/64);
                    
    if(gid%64==0){
        newX = newX-1;
    }

    if(newX>0){
        newX = 128*(gid-(newX*64)); 
    }else{
        newX = (gid*128);
    }
    
    return newX;
}

int Map::NewCoordY(int gid){
    
    int newY;
    
    newY = (gid/64)*128;
                    
    if(gid%64==0){
        newY = newY-128;
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


bool Map::putHitbox(Player *rath){
    
    colisiona = false;
    
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            //Recorremos la capa hitbox
            int gid = _tilemap[1][y][x];
                    
            if(gid>0){
                //Metemos las hitbox
                
               Coordinate prueba = Coordinate(_tilemapSprite[1][y][x]->getPosition());
      
               //Primera -> sup.Izq
               //Segunda -> inf.izq
               //Tercera -> inf.der
               //Cuarta -> sup.der
               
               /*if(((prueba.x==rath->getCoordinate()->x) && (prueba.y<rath->getCoordinate()->y) && (prueba.y+128>rath->getCoordinate()->y))
                       || (prueba.y==rath->getCoordinate()->y) && (prueba.x<rath->getCoordinate()->x)){*/
               
               //x rath < x pared, x pared < x rath+128 | y rath < y pared, y pared < y rath128
               //x rath < x pared, x pared < x rath+128 | y rath < y pared+128, y pared+128 < y rath+128
               //x rath < x pared+128, x pared+128 < x rath+128 | y rath < y pared+128, y pared+128 < y rath+128
               //x rath < x pared+128, x pared+128 < x rath+128 | y rath < y pared, y pared < y rath+128
               
               /*if(((prueba.x > rath->getCoordinate()->x) && (prueba.x < rath->getCoordinate()->x+128) && (prueba.y > rath->getCoordinate()->y) && (prueba.y < rath->getCoordinate()->y+128)) 
                       || ((prueba.x > rath->getCoordinate()->x) && (prueba.x < rath->getCoordinate()->x+128) && (prueba.y+128 > rath->getCoordinate()->y) && (prueba.y+128 < rath->getCoordinate()->y+128))
                       || ((prueba.x+128 > rath->getCoordinate()->x) && (prueba.x+128 < rath->getCoordinate()->x+128) && (prueba.y+128 > rath->getCoordinate()->y) && (prueba.y+128 < rath->getCoordinate()->y+128))
                       || ((prueba.x+128 > rath->getCoordinate()->x) && (prueba.x+128 < rath->getCoordinate()->x+128) && (prueba.y > rath->getCoordinate()->y) && (prueba.y < rath->getCoordinate()->y+128))){*/
                  
               if(((rath->getCoordinate()->x < prueba.x) && (prueba.x < rath->getCoordinate()->x + 128) && (rath->getCoordinate()->y < prueba.y) && (prueba.y < rath->getCoordinate()->y+128)) ||
((rath->getCoordinate()->x < prueba.x) && (prueba.x < rath->getCoordinate()->x + 128) && (rath->getCoordinate()->y < prueba.y + 128) && (prueba.y +128 < rath->getCoordinate()->y + 128)) ||
((rath->getCoordinate()->x < prueba.x + 128) && (prueba.x + 128 < rath->getCoordinate()->x + 128) && (rath->getCoordinate()->y < prueba.y + 128) && (prueba.y +128 < rath->getCoordinate()->y + 128)) ||
((rath->getCoordinate()->x < prueba.x + 128) && (prueba.x + 128 < rath->getCoordinate()->x + 128) && (rath->getCoordinate()->y < prueba.y) && (prueba.y < rath->getCoordinate()->y+128))){
colisiona = true;
}
                /*colisiona = true;
               }*/
            }
        }
    }
    
    return colisiona;
}