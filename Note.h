#ifndef NOTE_H
#define NOTE_H

#include <iostream>

#include "libs/Hitbox.h"
#include "libs/Sprite.h"
#include "libs/Text.h"

class Note {
private:
    Hitbox *hitbox;
    Sprite *noteSprite;
    Sprite *backgroundSprite;
    Text   *text;
    bool taken;
public:
    /**
     * Crea el objeto nota
     * @param nTex: Textura de la nota
     * @param nRect: Zona en la que imprimir la nota
     * @param bTex: Textura del fondo de la nota 
     * @param bRect: Zona en la que imprimir el fondo de la nota
     * @param f: Fuente de la nota
     */
    Note(Texture *nTex, Rect<float> nRect, Texture *bTex, Rect<float> bRect, Font *f);
    virtual ~Note();
    
    /**
     * Actualiza la posicion de la nota
     * @param nCoor: Coordenadas de la nota (tipo coord)
     */
    void setPosition(Coordinate nCoor);
    
    /**
     * Actualiza la posicion del fondo de la nota
     * @param bCoor: Coordenadas del fondo de la nota (tipo coord)
     */
    void setBackgroundPosition(Coordinate bCoor);
    
    /**
     * Actualiza la posicion del texto de la nota
     * @param str: Texto de la nota
     * @param color: Color del texto
     * @param outlineColor: Color del borde
     * @param outlineSize: Color del tamano del borde
     * @param size: tamano del texto
     */
    void setText(std::string str, sf::Color color, sf::Color outlineColor, int outlineSize, int size);
    
    /**
     * Actualiza si la nota es recogida o no
     */
    void setTaken();
    
    /**
     * Colision entre la nota y el jugador
     * @param other: Hitbox del jugador
     * @return 
     */
    bool collision(Hitbox *other);
    
    Text   *getText() { return text; }
    Hitbox *getHitbox() { return hitbox; }
    Sprite *getNoteSprite(){return noteSprite;}
    Sprite *getBackgroundSprite(){return backgroundSprite;}
    bool getTaken() { return taken; }
};

#endif /* NOTE_H */
