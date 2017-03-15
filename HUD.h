#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <vector>
#include "Sprite.h"

class HUD {
    
    private:
        Sprite *background;
        std::vector<Sprite*> *guns;
        std::vector<Sprite*> *gunsOff;
        Sprite *playerHP;
        Sprite *bossHP;
        Sprite *flashCooldown;
        
        int activeGun;
        
    public:
        HUD(Sprite *bg, std::vector<Sprite*> *gs, std::vector<Sprite*> *gsO, Sprite *pHP, Sprite *bHP, Sprite *fC);
        virtual ~HUD();
        
        void changeActiveGun(int gun);
        void changePlayerLife(int life);
        void activeBossLife(int life);
        void changeBossLife(int life);
        void changeFlashCooldown();
        
        bool drawHUD(sf::RenderWindow *window, int maxLife, int life,  int maxLifeBoss, int lifeBoss);
        void drawGun(sf::RenderWindow *window);
        void drawPlayerHP(sf::RenderWindow *window, int maxLife, int life);
        void drawBossHP(sf::RenderWindow *window, int maxLifeBoss, int lifeBoss);

        
};

#endif /* HUD_H */