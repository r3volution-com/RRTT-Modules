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
        float firstGunCooldown;
        float secondGunCooldown;
        
        int activeGun;
        int maxLifeBoss;
        int lifeBoss;
        int maxLifePlayer;
        int lifePlayer;
        
    public:
        HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC, Sprite *fCO);
        virtual ~HUD();
        
        void changeActiveGun(int gun);
        void changeMaxLifePlayer(int maxLife);
        void changeLifePlayer(int life);
        void changeMaxLifeBoss(int maxLife);
        void changeLifeBoss(int life);
        void changeFlashCooldown(int cooldown);
        void changeFirstGunCooldown(int cooldown);
        void changeSecondGunCooldown(int cooldown);
        
        bool drawHUD(sf::RenderWindow *window);
        void drawGun(sf::RenderWindow *window);
        void drawPlayerHP(sf::RenderWindow *window);
        void drawBossHP(sf::RenderWindow *window);
        void drawFlash(sf::RenderWindow *window);
        void drawFlashCooldown(sf::RenderWindow *window);
        
        
        void resetClock();
        
        //void useFirstGun()
        
};

#endif /* HUD_H */