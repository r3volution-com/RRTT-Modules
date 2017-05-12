#include "Hitbox.h"

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
    
    std::cout << "Metrics: aix" << aminx << " aiy" << aminy << " aax" << amaxx << " aay" << amaxy << " bix" << bminx << " biy" << bminy << " bax" << bmaxx << " bay" << bmaxy << "\n";

    // Return early if a & b are already overlapping
    //if(this->checkCollision(other)) return outVel;

    // Treat b as stationary, so invert v to get relative velocity
    speed.x = speed.x*-1;
    speed.y = speed.y*-1;
    
    std::cout << "Speed " << speed << " " << outVel<<"\n";

    float hitTime = 0.0f;
    float outTime = 1.0f;
    Coordinate overlapTime(0,0);

    // X axis overlap
    if(speed.x < 0) {
        if(bmaxx < aminx) return outVel;
        if(bmaxx > aminx) outTime = std::min((aminx - bmaxx) / speed.x, outTime);

        if(amaxx < bminx) {
            overlapTime.x = (amaxx - bminx) / speed.x;
            hitTime = std::max(overlapTime.x, hitTime);
        }
    }
    else if(speed.x > 0) {
        if(bminx > amaxx) return outVel;
        if(amaxx > bminx) outTime = std::min((amaxx - bminx) / speed.x, outTime);

        if(bmaxx < aminx) {
            overlapTime.x = (aminx - bmaxx) / speed.x;
            hitTime = std::max(overlapTime.x, hitTime);
        }
    }

    if(hitTime > outTime) return outVel;

    //=================================

    // Y axis overlap
    if(speed.y < 0) {
        if(bmaxy < aminy) return outVel;
        if(bmaxy > aminy) outTime = std::min((aminy - bmaxy) / speed.y, outTime);

        if(amaxy < bminy) {
            overlapTime.y = (amaxy - bminy) / speed.y;
            hitTime = std::max(overlapTime.y, hitTime);
        }           
    } else if(speed.y > 0) {
        if(bminy > amaxy) return outVel;
        if(amaxy > bminy) outTime = std::min((amaxy - bminy) / speed.y, outTime);

        if(bmaxy < aminy) {
            overlapTime.y = (aminy - bmaxy) / speed.y;
            hitTime = std::max(overlapTime.y, hitTime);
        }
    }

    if(hitTime > outTime) return outVel;

    // Scale resulting velocity by normalized hit time
    outVel.x = speed.x * -1 * hitTime;
    outVel.y = speed.y * -1 * hitTime;

    // Hit normal is along axis with the highest overlap time
    /*if(overlapTime.x > overlapTime.y) {
        hitNormal = new Vector2(Mathf.Sign(speed.x), 0);
    } else {
        hitNormal = new Vector2(0, Mathf.Sign(speed.y));
    }*/

    return outVel;
}