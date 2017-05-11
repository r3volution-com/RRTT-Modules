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

float Hitbox::resolveCollision(Hitbox *other, Coordinate speed){
    float xInvEntry, yInvEntry;
    float xInvExit, yInvExit;
	
    // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
    float xEntry, yEntry;
    float xExit, yExit;

    // find the distance between the objects on the near and far sides for both x and y
    if (speed.x > 0.0f) {
        xInvEntry = other->hitbox->left - (hitbox->left + hitbox->width);
        xInvExit = (other->hitbox->left + other->hitbox->width) - hitbox->left;
    } else if (speed.x < 0.0f) {
        xInvEntry = (other->hitbox->left + other->hitbox->width) - hitbox->left;
        xInvExit = other->hitbox->left - (hitbox->left + hitbox->width);
    }

    if (speed.x == 0.0f) {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    } else {
        xEntry = xInvEntry / speed.x;
        xExit = xInvExit / speed.x;
    }

    if (speed.y > 0.0f) {
        yInvEntry = other->hitbox->top - (hitbox->top + hitbox->height);
        yInvExit = (other->hitbox->top + other->hitbox->height) - hitbox->top;
    } else if (speed.y < 0.0f) {
        yInvEntry = (other->hitbox->top + other->hitbox->height) - hitbox->top;
        std::cout << "("<<other->hitbox->top <<"+"<< other->hitbox->height<<")-"<< hitbox->top<<"="<<yInvEntry<<"\n";
        yInvExit = other->hitbox->top - (hitbox->top + hitbox->height);
    }

    if (speed.y == 0.0f) {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    } else {
        std::cout << yInvEntry << " " << yInvExit << "\n";
        yEntry = yInvEntry / speed.y;
        yExit = yInvExit / speed.y;
        std::cout << yEntry << " " << yExit << "\n";
    }
	
    // find the earliest/latest times of collision
    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);
	
    // if there was no collision
    if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f) {
        //normalx = 0.0f;
        //normaly = 0.0f;
        std::cout << "a: " << entryTime << " " << exitTime << " " << xEntry << " " << yEntry << "\n";
        return 1.0f;
    }       		
        // calculate normal of collided surface
        /*if (xEntry > yEntry) {
            if (xInvEntry < 0.0f) {
                normalx = 1.0f;
                normaly = 0.0f;
            } else {
                normalx = -1.0f;
                normaly = 0.0f;
            }
        } else {
            if (yInvEntry < 0.0f) {
                normalx = 0.0f;
                normaly = 1.0f;
            } else {
                normalx = 0.0f;
		normaly = -1.0f;
            }
        }*/

    // return the time of collision
    return entryTime;
}