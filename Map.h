#ifndef MAP_H
#define MAP_H

#include <tinyxml2.h>
#include "libs/Sprite.h"
#include "Enemy.h"
#include "libs/json.hpp"

using namespace tinyxml2;

class Map {
    private:
        
        XMLElement* map;
        XMLElement* tileset;
        XMLElement* img;       
        XMLElement *layer;
        XMLElement *objectgroup;
        XMLElement **data;
        XMLElement *capas;
        int ***_tilemap;
        std::vector<Hitbox*> *muros;
        bool colisiona;
        Texture *_tilesetTexture;
        
    public:
        XMLDocument doc;
        int _width, _height, _tileWidth, _tileHeight, _columns;
        std::vector<float> _objectX, _objectY, _objectW, _objectH;
        const char *filename;
        int _numLayers;
        int _activeLayer;
        //Para saber si mostrar todo el mapa o solo una capa
        bool todo=true;
        Sprite ****_tilemapSprite;
        
        Map(const char* ruta, const char* texture);
        
        virtual ~Map();
        
        /**
         * Almacena cada posicion de data (cada posicion equivale a una capa). Todas las etiquetas son tile
         */
        void dataTiles();
        
        
        /**
         * Crea la matriz de sprites (_tilesetSprite) 3D en la que se multiplica el rect por el gid al que pertenece a la hora de crear el sprite  
         */
        void matrizSprites();
        
        /**
         * Obtencion de una nueva coordenada X para el sprite del tile
         * @param gid: Gid de la coordenada
         */
        int NewCoordX(int gid);
        
        /**
         * Obtencion de una nueva coordenada Y para el sprite del tile
         * @param gid: Gid de la coordenada
         */
        int NewCoordY(int gid);
        
        /**
         * Selecciona la capa a mostrar, en caso de pasarle por parametro un numero superior al numero de capas almacenadas, se mostrará por defecto a la capa 0
         * @param layer
         */
        void setActiveLayer(int layer);
        
        /**
         * Dibuja el mapa por panralla
         * @param window: Pantalla sobre la que se dibuja
         */
        void dibujarMapa(sf::RenderWindow *window);
        
        /**
         * Accede al gid del tile en el que se encuentre el enemigo
         * @param enemy: Enemigo en el gid
         * @param id1: Id del jugador
         * @param id2: Id del enemigo
         */
        int getGid(Enemy *enemy, int id1, int id2);
        
        
        
        Hitbox *getColHitbox(int i){return muros->at(i);}
        std::vector<Hitbox*> *getMuros(){return muros;}
};

#endif /* MAP_H */
