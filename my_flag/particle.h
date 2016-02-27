#ifndef PARTICLE_H
#define PARTICLE_H

#include "foundation.h"

class Particle
{
public:
    // constructors/destructor
    Particle();
    Particle(float x, float y, float z);
    Particle(vec3 position, vec3 velocity, vec3 acceleration);
    ~Particle();

    // attributes
    float mass;
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 force;
    vec3 externalForce;
    vec3 springForce;
    vec3 gravityForce;
    bool pinned = false;



    // draw function
    void draw();

};

#endif // PARTICLE_H
