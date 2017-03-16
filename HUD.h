#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "Font.h"
#include "Text.h"

class HUD {
    
    private:
        Sprite *background;
        std::vector<Sprite*> *guns;
        std::vector<Sprite*> *gunsOff;
        std::vector<Sprite*> *gunsCooldown;
        Sprite *playerHP;
        Sprite *bossHP;
        Sprite *flash;
        Sprite *flashCooldown;
        
        sf::Clock *clock;
        
        Sprite *textSprite;
        Text *talker;
        Text *currentText;
        Font *font;
        
        float timeFlash;
        float firstGunCooldown;
        float secondGunCooldown;
        
        int activeGun;
        int maxLifeBoss;
        int lifeBoss;
        int maxLifePlayer;
        int lifePlayer;
        
    public:
        HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC, Sprite *cool, std::vector<Sprite*> *gCd);
        virtual ~HUD();
        
        void changeActiveGun(int gun);
        void changeMaxLifePlayer(int maxLife);
        void changeLifePlayer(int life);
        void changeMaxLifeBoss(int maxLife);
        void changeLifeBoss(int life);
        void changeFlashCooldown(int cooldown);
        void changeFirstGunCooldown(int cooldown);
        void changeSecondGunCooldown(int cooldown);
        
        void setTextLayer(float x, float y, Sprite *sp, Font *f);
        void setTLayerTalker(std::string s, float x, float y);
        void setTLayerText(std::string s, float x, float y);
        void setTLayerTextParams(int size, sf::Color fillColor, sf::Color outlineColor);
        
        bool drawHUD(sf::RenderWindow *window);
        void drawGun(sf::RenderWindow *window);
        void drawPlayerHP(sf::RenderWindow *window);
        void drawBossHP(sf::RenderWindow *window);
        void drawFlash(sf::RenderWindow *window);
        
        bool drawFlashCooldown(sf::RenderWindow *window);
        bool drawGunCooldown(sf::RenderWindow *window);
        
        void resetClock();
};

#endif /* HUD_H */