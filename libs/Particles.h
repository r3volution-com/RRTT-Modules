#ifndef PARTICLES_H
#define PARTICLES_H

#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include "Texture.h"
#include "Rect.h"

class Particles {
    private:
        Texture *texture;
        thor::ParticleSystem *system;
        thor::UniversalEmitter *emitter;
        thor::Connection c;
        
        sf::Clock *clock;
    public:
        Particles(Texture *tex);
        virtual ~Particles();
        
        void setProperties(int rate, float minLifetime, float maxLifetime);
        void setGravity(float force);
        void setFading(float from, float to);
        void setParticlePosition(thor::Distribution<sf::Vector2f> particlePosition);
        void setParticleRotation(thor::Distribution<float> particleRotation);
        void setParticleScale(thor::Distribution<sf::Vector2f> particleScale);
        void setParticleSpeed(thor::Distribution<sf::Vector2f> particleVelocity);
        void setParticleRotationSpeed(thor::Distribution<float> particleRotationSpeed);
        
        void addParticle(Rect<float> rect);
        
        void start();
        void start(float time);
        void update();
        void stop();
        
        void draw();
};

#endif /* PARTICLES_H */