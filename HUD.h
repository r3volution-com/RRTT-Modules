#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <vector>
#include "Sprite.h"
#include <SFML/Graphics.hpp>


class HUD {
    
    private:
        Sprite *background;
        std::vector<Sprite*> *guns;
        std::vector<Sprite*> *gunsOff;
        Sprite *playerHP;
        Sprite *bossHP;
        Sprite *flash;
        Sprite *flashCooldown;
        
        sf::Clock *clock;
        
        float timeFlash;
        int activeGun;
        int maxLifeBoss;
        int lifeBoss;
        int maxLife;
        int life;
        
    public:
        HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC, Sprite *fCO);
        virtual ~HUD();
        
        void changeActiveGun(int gun);
        
        bool drawHUD(sf::RenderWindow *window);
        void drawGun(sf::RenderWindow *window);
        void drawPlayerHP(sf::RenderWindow *window);
        void drawBossHP(sf::RenderWindow *window);
        void drawFlash(sf::RenderWindow *window);
        bool drawFlashCooldown(sf::RenderWindow *window);
        void resetClock();
        
};

#endif /* HUD_H */