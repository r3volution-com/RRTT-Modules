#ifndef NOTE_H
#define NOTE_H

#include "Hitbox.h"
#include "Sprite.h"
#include "Text.h"

class Note {
private:
    Hitbox *hitbox;
    Sprite *noteSprite;
    Sprite *backgroundSprite;
    Text   *text;
    bool taken;
public:
    Note(Texture *nTex, Rect<float> nRect, Texture *bTex, Rect<float> bRect, Font *f);
    virtual ~Note();
    
    void setPosition(Coordinate nCoor);
    void setBackgroundPosition(Coordinate bCoor);
    void setText(std::string str, sf::Color color, sf::Color outlineColor, int outlineSize, int size);
    void setTaken();
    
    bool collision(Hitbox *other);
    
    Text   *getText() { return text; }
    Hitbox *getHitbox() { return hitbox; }
    Sprite *getNoteSprite(){return noteSprite;}
    Sprite *getBackgroundSprite(){return backgroundSprite;}
    bool getTaken() { return taken; }
};

#endif /* NOTE_H */