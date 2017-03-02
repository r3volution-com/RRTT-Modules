#include "Player.h"

Player::Player() : Entity(){
}

Player::~Player() {
}

/*void Player::changeGun(Arma g){
 * 
 * }
 */

void Player::flash(int dirX, int dirY){
    
}

void Player::respawn(){
    
}

void Player::gunAttack(){
    
}

void Player::damage(int dmg){
    if (hp-dmg <= 0) die();
    else hp -= dmg;
}