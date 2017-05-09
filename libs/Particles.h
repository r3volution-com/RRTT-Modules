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
        void setTransformProperties(thor::Distribution<sf::Vector2f> particlePosition, thor::Distribution<float> particleRotation, thor::Distribution<sf::Vector2f> particleScale);
        void setTransformSpeed(thor::Distribution<sf::Vector2f> particleVelocity, thor::Distribution<float> particleRotationSpeed);
        
        void addParticle(Rect<int> rect);
        
        void start();
        void start(float time);
        void update();
        void stop();
        
        void draw();
};

#endif /* PARTICLES_H */