#include "Hitbox.h"
#include "Animation.h"

Hitbox::Hitbox(float x, float y, int w, int h) {
    hitbox = new sf::Rect<float>(x, y, w, h);
}

Hitbox::Hitbox(Rect<float> nRect){
    hitbox = new sf::Rect<float>(nRect.x, nRect.y, nRect.w, nRect.h);
}

Hitbox::~Hitbox() {
    delete hitbox;
    hitbox = NULL;
}

void Hitbox::setPosition(float x, float y){
    hitbox->left = x;
    hitbox->top = y;
}

void Hitbox::setPosition(Coordinate newCoor){
    hitbox->left = newCoor.x;
    hitbox->top = newCoor.y;
}

bool Hitbox::checkCollision(Hitbox *other){
    return hitbox->intersects(*other->hitbox);
}

Coordinate Hitbox::resolveCollision(Hitbox *other, Coordinate speed){
    //Initialise out info
    Coordinate outVel = speed;
    
    float aminx = hitbox->left;
    float aminy = hitbox->top;
    float amaxx = hitbox->left+hitbox->width;
    float amaxy = hitbox->top+hitbox->height;
    
    float bminx = other->hitbox->left;
    float bminy = other->hitbox->top;
    float bmaxx = other->hitbox->left+other->hitbox->width;
    float bmaxy = other->hitbox->top+other->hitbox->height;
    
    float correctX = 0.0f;
    float correctY = 0.0f;
    
    if (speed.x < 0){
        correctX = aminx - bmaxx;
        std::cout << "x menor: " << aminx << "-" << bmaxx << "=" << correctX << "\n";
        if (correctX < speed.x || correctX > 0 ) return outVel;
    } else if (speed.x > 0) { 
        correctX = bminx - amaxx;
        std::cout << "x mayor: " << bminx << "-" << amaxx << "=" << correctX << "\n";
        if (correctX > speed.x || correctX < 0) return outVel;
    }
    
    if (speed.y < 0){
        correctY = aminy - bmaxy;
        std::cout << "y menor: " << aminy << "-" << bmaxy << "=" << correctY << "\n";
        if (correctY < speed.y || correctY > 0) return outVel;
        else correctY = speed.y - correctY;
    } else if (speed.y > 0){
        correctY = amaxy - bminy;
        std::cout << "y mayor: " << amaxy << "-" << bminy << "=" << correctY << "\n";
        if (correctY > speed.y || correctY < 0) return outVel;
        else correctY = speed.y - correctY;
    }
    
    std::cout << correctX << " " << speed.x << " " << correctY << " " << speed.y << "\n";
    
    if (speed.x != 0) outVel.x = correctX / speed.x;
    if (speed.y != 0) outVel.y = correctY / speed.y;
    std::cout << "\n" << speed.y << " " << outVel << "\n";
    
    return outVel;
}