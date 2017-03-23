#include "Note.h"
#include <iostream>

Note::Note(float x, float y, int w, int h, Sprite *sp, Sprite *sp2) {
    hitbox = new Hitbox(x, y, w, h);
    width = w;
    height = h;
    noteSprite = sp;
    backgroundSprite = sp2;
    sp->setPosition(x,y);
}


Note::~Note() {
    
}

bool Note::collision(Hitbox *other){
    return hitbox->checkCollision(other);
}
