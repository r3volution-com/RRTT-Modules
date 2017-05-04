#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include "../../tinyxml2/tinyxml2.h"
#include "../../libs/Sprite.h"
#include "../../Map.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]) {

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1400, 900), "RRTT: Map Test");
    
    //INICIO PRUEBAS
    
    Map *mapa = new Map("resources/test.tmx");
           
    cout << "0-> No ha habido errores cargando el mapa: " << mapa->doc.ErrorID() << "\n";
    
    cout << "Anchura: " << mapa->_width << "\n";
    cout << "ALtura: " << mapa->_height << "\n";
    cout << "TileWidth: " << mapa->_tileWidth << "\n";
    cout << "TIleHeight: " << mapa->_tileHeight << "\n";
    
    cout << "Nombre de la imagen tileset: " << mapa->filename << "\n";
    
    cout << "Numero de capas: " << mapa->_numLayers << "\n";
    
        while (window->isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window->pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::MouseWheelMoved:
                    break;
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window->close();
                        break;
                        default:
                        break;
                    }
                break;
                default: break;
            }
        }
    
        //Seleccionamos la capa activa

        //Dibujando el mapa por pantalla (primera capa)
    
        window->clear();
        
        //Seleccionamos capa a mostrar, en caso de no elegir ninguna 
        //no hariamos la llamada y mostrariamos todo el mapa
        //mapa->setActiveLayer(3);
        
        //Llamamos a dibujarMapa
        mapa->dibujarMapa(window);
        
        window->display();

    }
    
    /*XMLDocument doc;
    doc.LoadFile( "resources/bosque.tmx" );
    
    cout << "0-> No ha habido errores cargando el mapa: " << doc.ErrorID() << "\n";
    
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
    
    //FIN PRUEBAS
    
    XMLElement *data[_numLayers];
    
    XMLElement *capas = map->FirstChildElement("layer");
    
    for(int i=0; i<_numLayers; i++){
        data[i] = capas->FirstChildElement("data")->FirstChildElement("tile");
        capas = capas->NextSiblingElement("layer");
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
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                
                data[l] = data[l]->NextSiblingElement("tile");
                
            }
        }
    }
    
    //Hacer matriz de sprites (_tilesetSprite) 3D en la que a la hora de crear el sprite se mustiplicase el rect por el gid al que pertenece
    //Creacion del array de sprites
    
    Texture *_tilesetTexture = new Texture("resources/tileset3.png");
    
    Rect <float> *medidas = new Rect <float> (448, 96, 32, 32);
    
    Sprite ****_tilemapSprite;
    
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
                    
                    //Obtenemos nueva coordenada x e y del rect medidas                   
                    int newY = (gid/16)*32;
                    
                    if(gid%16==0){
                        newY = newY-1;
                    }
                    
                    int newX = (gid/16);
                    
                    if(gid%16==0){
                        newX = newX-1;
                    }
                    
                    if(newX>0){
                        newX = 32*(gid-(newX*16)); 
                    }else{
                        newX= 0;
                    }
                    
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
    
    while (window->isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window->pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::MouseWheelMoved:
                    break;
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window->close();
                        break;
                        default:
                        break;
                    }
                break;
                default: break;
            }
        }
    
        //Seleccionamos la capa activa

        //Dibujando el mapa por pantalla (primera capa)
    
        window->clear();

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

        window->display();

    }
    */
    return 0;
}