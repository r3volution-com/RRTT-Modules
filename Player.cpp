#include "Player.h"

Player::Player(float x, float y, int w, int h, float sp) : Entity(x, y, w, h, sp){
}

Player::~Player() {
}

/*void Player::changeGun(Arma g){
 * 
 * }
 */

void Player::flash(int dirX, int dirY){
    
}

void Player::die(){
    
}

void Player::respawn(){
    
}

void Player::gunAttack(){
    
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}