#include "Animation.h"

Animation::Animation(Texture *t, Rect<float> *tRect) {
    //Copiamos las variables
    tex = t;
    spriteRect = tRect;
    
    //Creamos la animacion
    animations = new thor::AnimationMap<sf::Sprite, std::string>();
    
    //Creamos el sprite que va a usar
    sprite = new sf::Sprite(*tex->getTexture(), tRect->getIntRect());
}

Animation::~Animation() {
    delete tex; //ToDo mario: no se si tex deberia borrarse aqui
    delete spriteRect;
    delete sprite;
    delete clock;
    delete animations;
    delete animator;
    tex = NULL;
    spriteRect = NULL;
    sprite = NULL;
    clock = NULL;
    animations = NULL;
    animator = NULL;
}

void Animation::addAnimation(std::string name, Coordinate clipCoord, int nSprites, float duration) {
    thor::FrameAnimation temp;
    for (int i = 0; i < nSprites; i++){
        temp.addFrame(1.0f, sf::IntRect(clipCoord.x+(spriteRect->w*i), clipCoord.y, spriteRect->w, spriteRect->h));
    }
    animations->addAnimation(name, temp, sf::seconds(duration));
}

void Animation::changeAnimation(std::string name, bool loop){
    if (loop) animator->play() << name;
    else animator->play() << thor::Playback::loop(name);
}

void Animation::queueAnimation(std::string name, bool loop){
    if (loop) animator->queue() << name;
    else animator->queue() << thor::Playback::loop(name);
}

void Animation::initAnimator(){
    animator = new thor::Animator<sf::Sprite, std::string>(*animations);
    clock = new sf::Clock();
}

void Animation::updateAnimator(){
    animator->update(clock->restart());
    animator->animate(*sprite);
}


//Sprite Funcions
void Animation::setPosition(float x, float y){
    sprite->setPosition(x, y);
}
void Animation::setPosition(Coordinate newCoord){
    sprite->setPosition(newCoord.x, newCoord.y);
}
void Animation::setRotation(float r){
    sprite->setRotation(r);
}
/*
void Animation::setOrigin(float x, float y){
    sprite->setOrigin(x, y);
}
void Animation::move(float x, float y){
    sprite->move(x, y);
}*/