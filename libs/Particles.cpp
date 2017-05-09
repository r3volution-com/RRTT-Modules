#include "Particles.h"
#include "../Game.h"

Particles::Particles(Texture *tex) {
    texture = tex;
    system = new thor::ParticleSystem();
    clock = new sf::Clock();
    emitter = new thor::UniversalEmitter();
    
    system->setTexture(*texture->getTexture());
}

Particles::~Particles() {
    
}

void Particles::setProperties(int rate, float minLifetime, float maxLifetime){
    emitter->setEmissionRate(rate);
    if (minLifetime == maxLifetime) emitter->setParticleLifetime(sf::seconds(minLifetime));
    else emitter->setParticleLifetime(thor::Distributions::uniform(sf::seconds(minLifetime), sf::seconds(maxLifetime)));
}

void Particles::setTransformProperties(thor::Distribution<sf::Vector2f> particlePosition, thor::Distribution<float> particleRotation, thor::Distribution<sf::Vector2f> particleScale){
    emitter->setParticlePosition(particlePosition);
    emitter->setParticleRotation(particleRotation);
    emitter->setParticleScale(particleScale);
}

void Particles::setTransformSpeed(thor::Distribution<sf::Vector2f> particleVelocity, thor::Distribution<float> particleRotationSpeed){
    emitter->setParticleVelocity(particleVelocity);
    emitter->setParticleRotationSpeed(particleRotationSpeed);
}

void Particles::setGravity(float force){
    sf::Vector2f acceleration(0.f, force);
    thor::ForceAffector gravityAffector(acceleration);
    system->addAffector(gravityAffector);
}

void Particles::setFading(float from, float to){
    thor::FadeAnimation fader(from, to);
    system->addAffector(thor::AnimationAffector(fader));
}

void Particles::addParticle(Rect<int> rect){
    system->addTextureRect(rect.getIntRect());
}

void Particles::start(){
    c = system->addEmitter(*emitter);
    clock->restart();
}

void Particles::start(float time){
    system->addEmitter(*emitter, sf::seconds(time));
    clock->restart();
}

void Particles::update(){
    system->update(clock->restart());
}

void Particles::stop(){
    c.disconnect();
}

void Particles::draw(){
    Game::Instance()->window->draw(*system);
}