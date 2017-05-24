#ifndef CRYSTALS_H
#define CRYSTALS_H

#include <iostream>

#include "libs/Hitbox.h"
#include "libs/Sprite.h"
#include "libs/Particles.h"
#include "libs/Animation.h"

class Crystal {
private:
    Hitbox *hitbox;
    Animation *anim;
    bool touched;
    Particles *sparks;
    
    int damage;
public:
    /**
     * Creacion de un objeto de tipo cristal
     * @param tex: Textura del cristal
     * @param rect: Zona en la que se va a imprimir el cristal
     */
    Crystal(Texture *tex, Rect<float> rect, Texture *sparksTexture, Rect<float> sparksRect);
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
    
    void startSparks();
    
    void drawSparks();
    
    /**
     * Colision entre el cristal y el jugador
     * @param other: Hitbox del jugador
     * @return 
     */
    bool collision(Hitbox *other);
    
    void setDamage(int d) { damage = d; }
    
    Hitbox *getHitbox() { return hitbox; }
    Animation *getCrystalAnimation(){return anim;}
    bool getTouched() { return touched; }
    int getDamage(){ return damage; }
};

#endif /* CRYSTALS_H */