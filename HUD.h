#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "libs/Sprite.h"
#include "libs/Text.h"
#include "libs/Time.h"
#include "Button.h"
#include "libs/Sprite.h"
#include "libs/Text.h"

class HUD {
    private:
        Game *game;
        sf::RenderWindow *window;
        
        Sprite *background;
        Sprite *hud;
        std::vector<Sprite*> *guns;
        std::vector<Sprite*> *gunsOff;
        std::vector<Sprite*> *gunsCooldown;
        Sprite *playerHP;
        Sprite *bossHP;
        Sprite *flash;
        Sprite *flashCooldown;
        Sprite *die;
        
        Time *clockFlash; 
        Time *clockFirstGun; 
        Time *clockSecondGun; 
        
        Sprite *textSprite;
        Text *talker;
        Text *currentText;
        Font *font;
        
        Text *lifePlayerText;
        
        Button *buttonDie;
        
        bool firstGunUsed;
        bool secondGunUsed;
        bool flashUsed;
        
        float timeFlash;
        float firstGunCooldown;
        float secondGunCooldown;
        
        int activeGun;
        int maxLifeBoss;
        int lifeBoss;
        int maxLifePlayer;
        int lifePlayer;
        
        bool dieBool;
        
        bool flashModuleEnabled;
        bool gunsModuleEnabled;
        bool dieModuleEnabled;
        bool textModuleEnabled;
        
    public:
        /**
         * Crea el objeto HUD
         * @param bTex: Textura de fondo (puntero)
         * @param hTex: Textura de los bordes (puntero)
         * @param lTex: Textira de la vida (puntero)
         * @param f: Fuente del texto (puntero)
         * @param cF: Tiempo del flash (tipo time)
         */
        HUD(Texture *bTex, Texture *hTex, Texture *lTex, Font *f, Time *cF);
        virtual ~HUD();
        
        /**
         * Actualizar sprites de las armas
         * @param tex: Textura de las armas (puntero)
         */
        void setGuns(Texture *tex, Time *g1, Time *g2);
        
        /**
         * Actualizar los sprites del flash
         * @param tFlash: Textura del flash (puntero)
         * @param tCooldown: Textura del tiempo de cooldown (puntero)
         */
        void setFlash(Texture *tFlash, Texture *tCooldown, Time *f);
        
        /**
         * Sprite de muerte
         * @param dTex: Textura del sprite de muerte (puntero)
         */
        void setDieSprite(Texture *dTex);
        
        /**
         * Actualizar capa de texto
         * @param coord: Coordenadas de la capa de texto (tipo coord)
         * @param tRect: Zona en la que imprimir la capa de texto
         * @param tTex: Textura de la capa de texto
         */
        void setTextLayer(Coordinate coord, Rect<float> tRect, Texture *tTex);
        
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
         * Actualiza un boton
         * @param coor: Coordenadas del boton (tipo coord)
         * @param tex: Textura del boton
         * @param rect: Zona en la que imprimir el boton
         */
        void setButton(Coordinate coor, Texture* tex, Rect<float> rect);
        
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
        
        
        
        /*std::vector<Sprite*> getSpriteGunsOn(){return guns;}
        std::vector<Sprite*> getSpriteGunsOff(){return gunsOff;}
        std::vector<Sprite*> getSpriteGunsCooldown(){return gunsCooldown;}
        Sprite* getSpriteFlash(){return flash;}
        Sprite* getSpriteFlashCooldown(){return flashCooldown;}*/
        
        /**
         * Dibuja el hud
         * @param window: Ventana en la que dibujar
         * @return 
         */
        bool drawHUD(sf::RenderWindow *window);
        
        /**
         * Dibuja el arma
         * @param window: Ventana en la que dibujar
         */
        void drawGun(sf::RenderWindow *window);
        
        /**
         * Dibuja la vida del jugador
         * @param window: Ventana en la que dibujar
         */
        void drawPlayerHP(sf::RenderWindow *window);
        
        /**
         * Dibuja la vida del boss
         * @param window: Ventana en la que dibujar
         */
        void drawBossHP(sf::RenderWindow *window);
        
        /**
         * Dibuja el flash
         * @param window: Ventana en la que dibujar
         */
        void drawFlash(sf::RenderWindow *window);
        
        /**
         * Dibuja la capa de texto
         * @param window: Ventana en la que dibujar
         */
        void drawTextLayer(sf::RenderWindow *window);
        
        /**
         * Dibuja el enfriamiento del flash
         * @param window: Ventana en la que dibujar
         */
        void drawFlashCooldown(sf::RenderWindow *window);
        
        /**
         * Dibuja el enfriamiento del arma 
         * @param window: Ventana en la que dibujar
         */
        void drawGunCooldown(sf::RenderWindow *window);
        
        /**
         * Dibuja la muerte del personaje
         * @param window: Ventana en la que dibujar
         */
        void drawDie(sf::RenderWindow *window);
        
        /**
         * Comprueba si el personaje esta muerto
         */
        bool checkDie();
        
        /**
         * Reinicia el reloj del flash
         */
        void resetClockFlash();
        
        /**
         * Reinicia el reloj
         */
        void resetClock();
        
        /**
         * Reinicia los stats
         */
        void resetStats();
        
        Button* getButton() { return buttonDie; }
};

#endif /* HUD_H */
