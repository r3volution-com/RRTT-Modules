#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "libs/Rect.h"
#include "libs/Sprite.h"
#include "libs/Text.h"
#include "libs/Time.h"
#include "Button.h"

class HUD {
    private:
        Texture *tex;
        Font *font;
        
        Rect<float> *cooldownRect;
        
        std::vector<Sprite*> guns;
        std::vector<Sprite*> gunsOff;
        std::vector<Sprite*> gunsCooldown;
        std::vector<Time*> gunTimers;
        int activeGun;
        
        Sprite *playerHP;
        Text *lifePlayerText;
        int maxLifePlayer;
        int lifePlayer;
        
        Sprite *bossHP;
        int maxLifeBoss;
        int lifeBoss;
        
        Sprite *flash;
        Sprite *flashCooldown;
        Time *clockFlash; 
        
        Sprite *die;
        Button *buttonDie;
        bool dieBool;
        
        Sprite *textSprite;
        Text *talker;
        Text *currentText;
        
        bool flashModuleEnabled;
        bool gunsModuleEnabled;
        bool dieModuleEnabled;
        bool textModuleEnabled;
        bool bossModuleEnable;
    public:
        /**
         * Crea el objeto HUD
         * @param hTex: Textura de los bordes (puntero)
         * @param rTex: Textura del resto de recursos (puntero)
         * @param lRect: Vida
         * @param f: Fuente del texto (puntero)
         */
        HUD(Texture *rTex, Rect<float> lRect, Rect<float> cdRect, Font *f);
        virtual ~HUD();
        
        /**
         * Pues va a ser que no
         * @param rect: isma esto no
         * @param g: esta hecho
         */
        void addGun(Coordinate position, Rect<float> rect, Rect<float> rectOff, Time *g);
        
        /**
         * Pues va a ser que no
         * @param pos: isumaeru,
         * @param rect: isma esto no
         * @param f: esta hecho
         */
        void setFlash(Coordinate pos, Rect<float> rect, Time *f);
        
        /**
         * Sprite de muerte
         * @param dTex: Textura del sprite de muerte (puntero)
         * @param
         * @param
         * @param
         */
        void setDieScreen(Texture *dTex, Coordinate coor, Texture* tex, Rect<float> rect);
        
        /**
         * Actualizar capa de texto
         * @param coord: Coordenadas de la capa de texto (tipo coord)
         * @param tRect: Zona en la que imprimir la capa de texto
         * @param tTex: Textura de la capa de texto
         */
        void setTextLayer(Coordinate coord, Rect<float> tRect, Texture *tTex);
        
        /**
         * Actualiza la vida del jefe
         * @param tRect: Zona a en la que se imprime la vida
         */
        void setBossLife(Rect<float> tRect);
        
        /**
         * Actualiza el texto que muestra el npc
         * @param s: Texto que muestra el npc (tipo string)
         * @param x: Posicion del texto en la coordenada x
         * @param y: Posicion del texto en la coordenada y
         */
        void setTLayerTalker(std::string s, float x, float y);
        
        /**
         * Actualiza la capa de texto
         * @param s: String a pasar por texto
         * @param x: Coordenada x en la que situar el texto
         * @param y: Coordenada y en la que situar el texto
         */
        void setTLayerText(std::string s, float x, float y);
        
        /**
         * Actualiza los parametros del texto
         * @param size: Tamano del texto
         * @param fillColor: Color del texto
         * @param outlineColor: Color del bordeado del texto
         */
        void setTLayerTextParams(int size, sf::Color fillColor, sf::Color outlineColor);
        
        /**
         * Actualiza la vida del jugador
         */
        void setTextLifePlayer();
        
        /**
         * Cambia al arma activa
         * @param gun: Arma (tipo int)
         */
        void changeActiveGun(int gun);
        
        /**
         * Cambia la vida maxima del jugador
         * @param maxLife: Vida maxima (tipo int)
         */
        void changeMaxLifePlayer(int maxLife);
        
        /**
         * Cambia la vida del jugador
         * @param life: Vida del jugador (tipo int)
         */
        void changeLifePlayer(int life);
        
        /**
         * Cambia la vida maxima del boss
         * @param maxLife: Vida maxima del boss (tipo int)
         */
        void changeMaxLifeBoss(int maxLife);
        
        /**
         * Cambia la vida del boss
         * @param life: Vida del boss (tipo int)
         */
        void changeLifeBoss(int life);
        
        /**
         * Dibuja el hud
         * @param window: Ventana en la que dibujar
         * @return 
         */
        void drawHUD(bool onRange);
        
        /**
         * Dibuja el arma
         * @param window: Ventana en la que dibujar
         */
        void drawGun();
        
        /**
         * Dibuja la vida del jugador
         * @param window: Ventana en la que dibujar
         */
        void drawPlayerHP();
        
        /**
         * Dibuja la vida del boss
         * @param window: Ventana en la que dibujar
         */
        void drawBossHP();
        
        /**
         * Dibuja el flash
         * @param window: Ventana en la que dibujar
         */
        void drawFlash();
        
        /**
         * Dibuja la capa de texto
         * @param window: Ventana en la que dibujar
         */
        void drawTextLayer();
        
        /**
         * Dibuja el enfriamiento del flash
         * @param window: Ventana en la que dibujar
         */
        void drawFlashCooldown();
        
        /**
         * Dibuja el enfriamiento del arma 
         * @param window: Ventana en la que dibujar
         */
        void drawGunCooldown();
        
        /**
         * Dibuja la muerte del personaje
         * @param window: Ventana en la que dibujar
         */
        void drawDie();
        
        /**
         * Comprueba si el personaje esta muerto
         */
        bool playerDie();
        
        /**
         * Reinicia el reloj del flash
         */
        void resetClockFlash();
        
        /**
         * Reinicia el reloj
         */
        void resetClockGuns();
        
        /**
         * Reinicia los stats
         */
        void resetStats();
        
        Button* getButton() { return buttonDie; }
};

#endif /* HUD_H */
