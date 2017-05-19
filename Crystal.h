#ifndef CRYSTALS_H
#define CRYSTALS_H

#include <iostream>

#include "libs/Hitbox.h"
#include "libs/Sprite.h"
#include "Player.h"

class Crystal {
private:
    Hitbox *hitbox;
    Sprite *sprite;
    bool touched;
public:
    /**
     * Creacion de un objeto de tipo cristal
     * @param tex: Textura del cristal
     * @param rect: Zona en la que se va a imprimir el cristal
     */
    Crystal(Texture *tex, Rect<float> rect);
    virtual ~Crystal();
    
    /**
     * Actualiza la posicion del cristal
     * @param nCoor: Coordenadas de la nota (tipo coord)
     */
    void setPosition(Coordinate nCoor);
    
    /**
     * Actualiza si el cristal es tocado o no
     */
    void setTouched();
    
    /**
     * Colision entre el cristal y el jugador
     * @param other: Hitbox del jugador
     * @return 
     */
    bool collision(Hitbox *other);
    
    Hitbox *getHitbox() { return hitbox; }
    Sprite *getCrystalSprite(){return sprite;}
    bool getTouched() { return touched; }
};

#endif /* CRYSTALS_H */