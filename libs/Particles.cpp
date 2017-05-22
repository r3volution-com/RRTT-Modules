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
    delete system;
    delete emitter;
    delete clock;
    system = NULL;
    emitter = NULL;
    clock = NULL;
}

void Particles::setProperties(int rate, float minLifetime, float maxLifetime){
    emitter->setEmissionRate(rate);
    if (minLifetime == maxLifetime) emitter->setParticleLifetime(sf::seconds(minLifetime));
    else emitter->setParticleLifetime(thor::Distributions::uniform(sf::seconds(minLifetime), sf::seconds(maxLifetime)));
}

void Particles::setParticlePosition(thor::Distribution<sf::Vector2f> particlePosition){
    emitter->setParticlePosition(particlePosition);
}

void Particles::setParticleRotation(thor::Distribution<float> particleRotation){
    emitter->setParticleRotation(particleRotation);
}

void Particles::setParticleScale(thor::Distribution<sf::Vector2f> particleScale){
    emitter->setParticleScale(particleScale);
}

void Particles::setParticleRotationSpeed(thor::Distribution<float> particleRotationSpeed){
    emitter->setParticleRotationSpeed(particleRotationSpeed);
}

void Particles::setParticleSpeed(thor::Distribution<sf::Vector2f> particleVelocity){
    emitter->setParticleVelocity(particleVelocity);
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

void Particles::addParticle(Rect<float> rect){
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