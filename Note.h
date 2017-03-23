#ifndef NOTE_H
#define NOTE_H

#include "Hitbox.h"
#include "Sprite.h"

class Note {
private:
    int width;
    int height;
    float x;
    float y;
    Hitbox *hitbox;
    Sprite *noteSprite;
    Sprite *backgroundSprite;
    bool taken;
public:
    Note(float x, float y, int w, int h, Sprite *sp, Sprite *sp2);
    virtual ~Note();
    int getWidth() { return width; }
    int getHeight() { return height; }
    Hitbox *getHitbox() { return hitbox; }
    bool collision(Hitbox *other);
    Sprite *getNoteSprite(){return noteSprite;}
    Sprite *getBackgroundSprite(){return backgroundSprite;}
};

#endif /* NOTE_H */

