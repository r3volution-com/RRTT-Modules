#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include "tinyxml2/tinyxml2.h"
#include "libs/Sprite.h"
#include "Map.h"
#include "Level.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]) {

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1400, 900), "RRTT: Map Test");
    sf::View view(sf::FloatRect(0,0,4096,4096));
    //INICIO PRUEBAS
    
    Level *level = new Level (1);
           
    /*COMPROBACIONES MAPA
     * 
     * Map *map = new Map("resources/bosque.tmx");
     * 
     * cout << "0-> No ha habido errores cargando el mapa: " << mapa->doc.ErrorID() << "\n";
    
    cout << "Anchura: " << mapa->_width << "\n";
    cout << "ALtura: " << mapa->_height << "\n";
    cout << "TileWidth: " << mapa->_tileWidth << "\n";
    cout << "TIleHeight: " << mapa->_tileHeight << "\n";
    
    cout << "Nombre de la imagen tileset: " << mapa->filename << "\n";
    
    cout << "Numero de capas: " << mapa->_numLayers << "\n";*/
    
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
        window->setView(view);
        //Dibujamos el mapa map->dibujarMapa(window);
        level->drawAll(window);
        
        window->display();

    }

    return 0;
}