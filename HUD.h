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
        HUD(Texture *bTex, Texture *hTex, Texture *lTex, Font *f, Time *cF);
        virtual ~HUD();
        
        void setSpriteGuns(Texture *tex);
        void setFlashSprites(Texture *tFlash, Texture *tCooldown);
        void setDieSprite(Texture *dTex);
        void setTextLayer(Coordinate coord, Rect<float> tRect, Texture *tTex);
        void setTLayerTalker(std::string s, float x, float y);
        void setTLayerText(std::string s, float x, float y);
        void setTLayerTextParams(int size, sf::Color fillColor, sf::Color outlineColor);
        void setTextLifePlayer();
        void setButton(Coordinate coor, Texture* tex, Rect<float> rect);
        
        void changeActiveGun(int gun);
        void changeMaxLifePlayer(int maxLife);
        void changeLifePlayer(int life);
        void changeMaxLifeBoss(int maxLife);
        void changeLifeBoss(int life);
        void changeFlashCooldown(int cooldown);
        void changeFirstGunCooldown(int cooldown);
        void changeSecondGunCooldown(int cooldown);
        
        /*std::vector<Sprite*> getSpriteGunsOn(){return guns;}
        std::vector<Sprite*> getSpriteGunsOff(){return gunsOff;}
        std::vector<Sprite*> getSpriteGunsCooldown(){return gunsCooldown;}
        Sprite* getSpriteFlash(){return flash;}
        Sprite* getSpriteFlashCooldown(){return flashCooldown;}*/
        
        bool drawHUD(sf::RenderWindow *window);
        void drawGun(sf::RenderWindow *window);
        void drawPlayerHP(sf::RenderWindow *window);
        void drawBossHP(sf::RenderWindow *window);
        void drawFlash(sf::RenderWindow *window);
        void drawTextLayer(sf::RenderWindow *window);
        void drawFlashCooldown(sf::RenderWindow *window);
        void drawGunCooldown(sf::RenderWindow *window);
        void drawDie(sf::RenderWindow *window);
        
        bool checkDie();
        
        void resetClockFlash();
        void resetClock();
        void resetStats();
        
        Button* getButton() { return buttonDie; }
};

#endif /* HUD_H */
