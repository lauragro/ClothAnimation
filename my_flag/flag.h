#ifndef FLAG_H
#define FLAG_H

#include "spring.h"
#include "particle.h"

class Spring;
class Particle;

class Flag
{
public:
    // constructor/destructor
    Flag();
    ~Flag();

    // constants
    static const int particlesHigh = 12;
    static const int particlesWide = 18;

    // 12 spring method
    static const int numStructureSprings = (particlesHigh-1)*particlesWide + (particlesWide-1)*particlesHigh; // max 4 per particle
    static const int numShearSprings = 2*(particlesHigh-1)*(particlesWide-1); // max 4 per particle
    static const int numBendSprings = (particlesHigh-2) * particlesWide + (particlesWide-2) * particlesHigh; // max 4 per particle
    static const int numSprings = numStructureSprings + numShearSprings + numBendSprings;
    int implementedSprings = 0;

    // attributes
    float height;
    float width;
    float particleMass;
    float springConstant;
    float dampingConstant;

    // grid containing all particle pointers
    Particle *particles[particlesHigh][particlesWide];

    // array containing all spring pointers
    Spring *springs[numSprings];


};

#endif // FLAG_H
