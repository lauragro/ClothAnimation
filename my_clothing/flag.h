#ifndef FLAG_H
#define FLAG_H

#include "spring.h"
#include "particle.h"

#define SHEET "sheet"
#define BLANKET "blanket"

class Spring;
class Particle;

class Flag
{
public:
    // constructor/destructor
    Flag(int zCentre, float startHeight);
    ~Flag();

    void draw();

    // type of flag to make
    //char * type = SHEET;
    char * type = BLANKET;

    // constants
    static const int particlesHigh = 32; //12;
    static const int particlesWide = 32;

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


private:
    void createSheet(int zCentre);
    void createBlanket(int zCentre, float startHeight);

    void drawTriangle(Particle *p1, Particle *p2, Particle *p3, const vec3 colour);
    vec3 calcTriangleNormal(Particle *p1,Particle *p2,Particle *p3);

};

#endif // FLAG_H
