#include "Protagonista.h"

Protagonista::Protagonista() : Personaje(){
}

Protagonista::~Protagonista() {
}

/*void Protagonista::changeGun(Arma g){
 * 
 * }
 */

void Protagonista::flash(int dirX, int dirY){
    
}

void Protagonista::respawn(){
    
}

void Protagonista::gunAttack(){
    
}

void Protagonista::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}